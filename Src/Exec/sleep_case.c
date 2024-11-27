/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_case.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:06:28 by nsauret           #+#    #+#             */
/*   Updated: 2024/11/27 15:53:39 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	get_to_bed_with_a_timer(t_data *data, int max_sleep)
{
	char	**cmd;
	pid_t	sleep_pid;

	cmd = ft_calloc(4, sizeof(char *));
	if (!cmd)
		return ;
	cmd[0] = "time";
	cmd[1] = "sleep";
	cmd[2] = ft_itoa(max_sleep);
	sleep_pid = fork();
	if (!sleep_pid)
	{
		execve("/usr/bin/time", cmd, data->env_array);
	}
	free(cmd);
	waitpid(sleep_pid, NULL, 0);
}

static void	get_to_bed(t_data *data, int max_sleep)
{
	char	**cmd;
	pid_t	sleep_pid;

	cmd = ft_calloc(3, sizeof(char *));
	if (!cmd)
		return ;
	cmd[0] = "sleep";
	cmd[1] = ft_itoa(max_sleep);
	sleep_pid = fork();
	if (!sleep_pid)
	{
		execve("/usr/bin/sleep", cmd, data->env_array);
	}
	free(cmd);
	waitpid(sleep_pid, NULL, 0);
}

int	sleep_case(t_data *data, t_pipex *pipex)
{
	if (pipex->max_sleep > 0)
	{
		if (pipex->have_time_cmd)
			get_to_bed_with_a_timer(data, pipex->max_sleep);
		else
			get_to_bed(data, pipex->max_sleep);
	}
	return (1);
}
