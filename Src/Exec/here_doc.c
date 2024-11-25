/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:34:03 by nsauret           #+#    #+#             */
/*   Updated: 2024/11/25 18:14:08 by nsauret          ###   ########.fr       */
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
	while (1)
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
	write(fd[1], here_doc, ft_strlen(here_doc));
	close(fd[1]);
	return (fd[0]);
}
