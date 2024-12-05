/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:34:03 by nsauret           #+#    #+#             */
/*   Updated: 2024/12/05 20:23:53 by jmiccio          ###   ########.fr       */
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
	if (open("/dev/tty", O_RDONLY) == -1)
		terminate(data, "Error reopening stdin\n", 1);
	data->exit_status = g_signal_pid;
	return (-1);
}

static void	loop(char **buffer, char **here_doc, char *argv)
{
	while (g_signal_pid != 130)
	{
		*buffer = NULL;
		*buffer = readline("> ");
		if (g_signal_pid == 130 || !*buffer)
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
	if (g_signal_pid == 130)
		return (sigint_handler(data, fd, buffer, here_doc));
	if (!buffer)
	{
		ft_printerr("minishell: here_doc: unexpected EOF\n");
		close(fd[1]);
		close(fd[0]);
		return (-1);
	}
	write(fd[1], here_doc, ft_strlen(here_doc));
	close(fd[1]);
	return (fd[0]);
}
