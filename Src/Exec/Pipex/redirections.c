/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:03:55 by nsauret           #+#    #+#             */
/*   Updated: 2024/11/07 16:17:47 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	redirection_input(t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->tokens->str, O_RDONLY);
	if (fd < 0)
	{
		perror(cmd->tokens->str);
		return (-1);
	}
	return (fd);
}

int	redirection_trunc(t_pipex *pipex, t_cmd *cmd)
{
	int	fd;

	if (pipex->exec->out != -2)
		close(pipex->exec->out);
	fd = open(cmd->tokens->str, O_CREAT | O_RDWR | O_TRUNC, 0000644);
	if (fd < 0)
	{
		perror(cmd->tokens->str);
		return (-1);
	}
	return (fd);
}
