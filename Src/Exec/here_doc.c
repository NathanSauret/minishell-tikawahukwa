/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:34:03 by nsauret           #+#    #+#             */
/*   Updated: 2024/11/20 16:03:36 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	end_here_doc(int fd, char *buffer, t_pipex *pipex)
{
	get_next_line(fd, 0);
	free(buffer);
	close(fd);
	pipex->exec->in = open(".heredoc", O_RDONLY);
	if (pipex->exec->in < 0)
	{
		unlink(".heredoc");
		exit_error_exec(pipex, 1, "here_doc");
	}
}

void	here_doc(char *argv, t_pipex *pipex)
{
	int		fd;
	char	*buffer;

	fd = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (fd < 0)
	{
		exit_error_exec(pipex, 1, ".here_doc");
		return ;
	}
	while (1)
	{
		write(1, "heredoc> ", 9);
		buffer = get_next_line(0, 1);
		if (buffer == NULL)
		{
			get_next_line(0, 0);
			return ;
		}
		if (!ft_strncmp(argv, buffer, ft_strlen(argv))
			&& ft_strlen(argv) == ft_strlen(buffer) - 1)
			break ;
		write(fd, buffer, ft_strlen(buffer) - 1);
		write(fd, "\n", 1);
		free(buffer);
	}
	end_here_doc(fd, buffer, pipex);
}
