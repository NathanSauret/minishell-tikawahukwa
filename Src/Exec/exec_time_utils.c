/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_time_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:46:09 by nsauret           #+#    #+#             */
/*   Updated: 2024/11/27 16:01:50 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exec_count_time(t_pipex *pipex)
{
	if (!ft_strncmp(pipex->exec->cmd[0], "time", 4))
		pipex->have_time_cmd = 1;
	if (!ft_strncmp(pipex->exec->cmd[0], "time", 4)
		&& !ft_strncmp(pipex->exec->cmd[1], "sleep", 5)
		&& ft_atoi(pipex->exec->cmd[2]) > pipex->max_sleep)
	{
		pipex->max_sleep = ft_atoi(pipex->exec->cmd[2]);
	}
	else if (!ft_strncmp(pipex->exec->cmd[0], "sleep", 5)
		&& ft_atoi(pipex->exec->cmd[1]) > pipex->max_sleep)
	{
		pipex->max_sleep = ft_atoi(pipex->exec->cmd[1]);
	}
}
