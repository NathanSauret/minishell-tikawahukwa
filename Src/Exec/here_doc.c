/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:34:03 by nsauret           #+#    #+#             */
/*   Updated: 2025/01/05 23:09:02 by jmiccio          ###   ########.fr       */
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

static void	err_malloc(t_data *data, char *buff, char *here_doc, int fd[2])
{
	if (buff)
		free(buff);
	if (here_doc)
		free(here_doc);
	close(fd[1]);
	close(fd[0]);
	terminate(data, ERR_MALLOC, 1);
}

static int	loop(char **buffer, char **here_doc, char *argv)
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
		if (!*buffer)
			return (0);
		if (!*here_doc)
		{
			*here_doc = ft_strdup(*buffer);
			free(*buffer);
		}
		else
			*here_doc = ft_strjoin(*here_doc, *buffer);
		if (!*here_doc)
			return (0);
	}
	return (1);
}

int	here_doc(t_data *data, char *argv)
{
	int		fd[2];
	char	*buffer;
	char	*here_doc;

	if (pipe(fd) == -1)
	{
		ft_printerr("pipe error\n");
		return (-1);
	}
	here_doc = NULL;
	buffer = NULL;
	signal(SIGINT, here_doc_handler);
	if (!loop(&buffer, &here_doc, argv))
		err_malloc(data, buffer, here_doc, fd);
	signals();
	if (g_signal == SIGINT)
		return (sigint_handler(data, fd, buffer, here_doc));
	if (!buffer)
		ft_printerr("minishell: here_doc: unexpected EOF\n");
	write(fd[1], here_doc, ft_strlen(here_doc));
	free(here_doc);
	close(fd[1]);
	data->pipex->exec->is_infile = 1;
	return (fd[0]);
}
