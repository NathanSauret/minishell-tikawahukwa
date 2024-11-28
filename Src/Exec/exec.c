/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:20:10 by nsauret           #+#    #+#             */
/*   Updated: 2024/11/28 17:50:00 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	finish_exec(t_data *data, t_pipex *pipex)
{
	int	status;

	close_pipes(pipex, data);
	free_parent(pipex, data);
	if (data->pid)
	{
		waitpid(data->pid, &status, 0);
		data->exit_status = WEXITSTATUS (status);
	}
	waitpid(-1, NULL, 0);
	// ft_printf("exit status: %d\n", data->exit_status);
}

static int	set_values(t_pipex *pipex, t_data *data)
{
	pipex->cmd_nb = data->num_of_pipe + 1;
	if (data->num_of_pipe > 0)
	{
		pipex->pipe = (int *)malloc(sizeof(int) * (data->num_of_pipe * 2));
		if (!pipex->pipe)
		{
			free_pipe(pipex);
			return (exit_error_exec(pipex, 1, "Error: pipe"));
		}
	}
	data->pid = 0;
	pipex->max_sleep = 0;
	pipex->have_time_cmd = 0;
	return (1);
}

int	exec(t_data *data)
{
	t_pipex	pipex;

	if (!data->num_of_pipe && !ft_strncmp(data->token->str, "exit", 4))
		return (ft_exit(data), -1);
	if (!set_values(&pipex, data))
		return (-1);
	if (!create_pipes(&pipex, data))
		return (-1);
	if (!prepare_for_exec(data, &pipex))
		return (finish_exec(data, &pipex), -1);
	if (!execute_commands(data, &pipex))
		return (finish_exec(data, &pipex), -1);
	finish_exec(data, &pipex);
	return (0);
}
