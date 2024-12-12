/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:20:10 by nsauret           #+#    #+#             */
/*   Updated: 2024/12/12 17:59:18 by j_sk8            ###   ########.fr       */
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
			if (WIFSIGNALED(status)
				&& (data->exit_status == SIGINT
					|| data->exit_status == SIGQUIT))
			{
				data->exit_status = 128 + WTERMSIG(status);
				if (data->exit_status == SIGINT || data->exit_status == SIGQUIT)
					data->is_nl = 1;
			}
			else if (pid == data->pid && WIFEXITED(status)
				&& !data->exit_status)
				data->exit_status = WEXITSTATUS(status);
		}
	}
	signal(SIGINT, handle_sigint);
}

static void	set_values(t_pipex *pipex, t_data *data)
{
	pipex->cmd_nb = data->num_of_pipe + 1;
	pipex->pipe = NULL;
	if (data->num_of_pipe > 0)
	{
		pipex->pipe = (int *)malloc(sizeof(int) * (data->num_of_pipe * 2));
		if (!pipex->pipe)
		{
			free_parent(pipex, data);
			terminate(data, ERR_MALLOC, 1);
		}
	}
	data->exit_status = 0;
	data->pipex = pipex;
}

int	exec(t_data *data)
{
	t_pipex	pipex;

	if (!data->num_of_pipe && !ft_strncmp(data->token->str, "exit", MAX_LENGTH))
		ft_exit(data, data->cmd->cmd);
	set_values(&pipex, data);
	create_pipes(&pipex, data);
	prepare_for_exec(data, &pipex);
	if (g_signal == SIGINT)
	{
		data->is_nl = 1;
		finish_exec(data, &pipex);
		return (0);
	}
	execute_commands(data, &pipex);
	finish_exec(data, &pipex);
	return (0);
}
