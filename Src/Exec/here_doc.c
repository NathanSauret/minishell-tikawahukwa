/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:34:03 by nsauret           #+#    #+#             */
/*   Updated: 2024/12/12 16:08:18 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	sigint_handler(t_data *data, int fd[2], char *buffer, char *here_doc)
{
	if (buffer)
		free(buffer);
	if (here_doc)
		free(here_doc);
	close(fd[1]);
	close(fd[0]);
	if (open("/dev/tty", O_RDONLY) == -1)
		terminate(data, " Error reopening stdin\n", 1);
	data->exit_status = 130;
	return (-1);
}

static void	loop(char **buffer, char **here_doc, char *argv)
{
	while (1)
	{
		*buffer = NULL;
		*buffer = readline("> ");
		if (g_signal == SIGINT || !*buffer)
			break ;
		if (!ft_strncmp(argv, *buffer, ft_strlen(argv))
			&& ft_strlen(argv) == ft_strlen(*buffer))
			break ;
		*buffer = ft_strjoin(*buffer, ft_strdup("\n"));
		if (!*here_doc)
		{
			*here_doc = ft_strdup(*buffer);
			free(*buffer);
		}
		else
			*here_doc = ft_strjoin(*here_doc, *buffer);
	}
}

int	here_doc(t_data *data, char *argv)
{
	int		fd[2];
	char	*buffer;
	char	*here_doc;

	if (pipe(fd) == -1)
		return (-1);
	here_doc = NULL;
	buffer = NULL;
	signal(SIGINT, here_doc_handler);
	loop(&buffer, &here_doc, argv);
	signals();
	if (g_signal == SIGINT)
		return (sigint_handler(data, fd, buffer, here_doc));
	if (!buffer)
		ft_printerr("minishell: here_doc: unexpected EOF\n");
	write(fd[1], here_doc, ft_strlen(here_doc));
	free(here_doc);
	close(fd[1]);
	return (fd[0]);
}
