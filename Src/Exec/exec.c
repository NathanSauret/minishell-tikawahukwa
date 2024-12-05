/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:20:10 by nsauret           #+#    #+#             */
/*   Updated: 2024/12/05 22:46:32 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	finish_exec(t_data *data, t_pipex *pipex)
{
	int		status;
	pid_t	pid;

	close_pipes(pipex, data);
	free_parent(pipex, data);
	pid = 1;
	while (pid > 0)
	{
		pid = waitpid(-1, &status, 0);
		if (pid > 0)
		{
			if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
				data->exit_status = 128 + WTERMSIG(status);
			else if (pid == g_signal_pid && WIFEXITED(status)
					&& !data->exit_status)
				data->exit_status = WEXITSTATUS(status);
		}
	}
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
	data->exit_status = 0;
	pipex->max_sleep = 0;
	pipex->have_time_cmd = 0;
	data->pipex = pipex;
	return (1);
}

int	exec(t_data *data)
{
	t_pipex	pipex;

	if (!data->num_of_pipe && !ft_strncmp(data->token->str, "exit", 4))
		return (ft_exit(data, data->cmd->cmd), -1);
	if (!set_values(&pipex, data))
		return (-1);
	if (!create_pipes(&pipex, data))
		return (-1);
	if (!prepare_for_exec(data, &pipex))
		return (finish_exec(data, &pipex), -1);
	if (g_signal_pid == 130)
		return (finish_exec(data, &pipex), 0);
	if (!execute_commands(data, &pipex))
		return (finish_exec(data, &pipex), -1);
	finish_exec(data, &pipex);
	return (0);
}
