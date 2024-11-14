/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_jeremy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 22:49:41 by j_sk8             #+#    #+#             */
/*   Updated: 2024/11/13 18:07:34 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exec_builtin(t_data *data)
{
	if (ft_strnstr((data->token->str), "exit", 4))
		return (ft_exit(data));
	return (1);
}

static int	child(t_data *data, t_exec *exec, t_pipex *pipex, char **env)
{

	g_signal_pid = fork();
	if (!g_signal_pid)
	{
		dup2(exec->in, 0);
		dup2(exec->out, 1);
		close_pipes(pipex, data);
		execve(exec->path, exec->cmd, env);
	}
	return (1);
}

void	exec_cmd(t_pipex *pipex, t_data *data, char **env)
{
	t_exec	*cmd;
	int		i;

	i = 0;
	cmd = pipex->exec;
	while (i < pipex->cmd_nb)
	{
		child(data, cmd, pipex, env);
		cmd = cmd->next;
		i++;
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
			pipe_free(pipex);
			return (exit_error_pipex(pipex, 1, "Error: pipe"));
		}
	}
	pipex->here_doc = 0;
	return (1);
}

int	exec2(t_data *data, char **env)
{
	t_pipex pipex;

	if (data->token->is_builtin)
		return (exec_builtin(data));
	else
	{
		set_values(&pipex, data);
		exec_cmd(&pipex, data, env);
	}
	return (1);
}
