/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:34:03 by nsauret           #+#    #+#             */
/*   Updated: 2024/12/03 23:30:14 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	here_doc(char *argv)
{
	int		fd[2];
	char	*buffer;
	char	*here_doc;

	if (pipe(fd) == -1)
		return (-1);
	here_doc = NULL;
	signal(SIGINT, here_doc_handler);
	while (!g_signal_pid)
	{
		buffer = readline("> ");
		if (buffer == NULL)
			return (-1);
		if (!ft_strncmp(argv, buffer, ft_strlen(argv))
			&& ft_strlen(argv) == ft_strlen(buffer))
			break ;
		buffer = ft_strjoin(buffer, ft_strdup("\n"));
		here_doc = ft_strjoin(ft_strdup(here_doc), buffer);
	}
	signals();
	if (g_signal_pid)
		return (-1);
	write(fd[1], here_doc, ft_strlen(here_doc));
	close(fd[1]);
	return (fd[0]);
}
