/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:11:51 by nathan            #+#    #+#             */
/*   Updated: 2025/01/03 20:32:33 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	exec_builtin(t_data *data, t_pipex *pipex)
{
	if (ft_strnstr((pipex->exec->cmd[0]), "cd", 2))
		return (ft_cd(data, data->env, pipex->exec->cmd));
	if (ft_strnstr((pipex->exec->cmd[0]), "echo", 4))
		return (ft_echo(pipex->exec->cmd));
	if (ft_strnstr((pipex->exec->cmd[0]), "env", 3))
		return (ft_env(data->env));
	if (ft_strnstr((pipex->exec->cmd[0]), "export", 6))
		return (ft_export(pipex->exec->cmd, data));
	if (ft_strnstr((pipex->exec->cmd[0]), "pwd", 3))
		return (ft_pwd());
	if (ft_strnstr((pipex->exec->cmd[0]), "unset", 5))
		return (ft_unset(pipex->exec->cmd, data));
	if (ft_strnstr((pipex->exec->cmd[0]), "exit", 4))
		ft_exit(data, pipex->exec->cmd);
	return (-1);
}

static void	lonely_child(t_data *data, t_pipex *pipex)
{
	int		res;

	res = exec_builtin(data, pipex);
	data->exit_status = res;
}

static void	pipe_handler(t_data *data, t_exec *exec, t_pipex *pipex)
{
	if (dup2(exec->out, STDOUT_FILENO) == -1)
		terminate(data, "dup2 error\n", 1);
	if (dup2(exec->in, STDIN_FILENO) == -1)
		terminate(data, "dup2 error\n", 1);
	if (exec->is_infile)
		close(exec->in);
	if (exec->is_outfile)
		close(exec->out);
	close_pipes(pipex, data);
}

static void	child(t_data *data, t_pipex *pipex)
{
	t_exec	*exec;
	int		res;

	data->pid = fork();
	if (data->pid == -1)
	{
		ft_printerr(" fork failed\n");
		data->exit_status = 1;
		return ;
	}
	res = -1;
	if (!data->pid)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		exec = pipex->exec;
		check_valid_cmd(data, exec);
		pipe_handler(data, exec, pipex);
		if (exec->is_builtin)
			res = exec_builtin(data, pipex);
		else
			res = execve(exec->path, exec->cmd, data->env_array);
		terminate(data, NULL, res);
	}
}

void	execute_commands(t_data *data, t_pipex *pipex)
{
	signal(SIGINT, SIG_IGN);
	while (pipex->exec)
	{
		if (!pipex->exec->cmd[0])
		{
			close_iofiles_and_free_prev_exec(pipex);
			continue ;
		}
		else if (!data->num_of_pipe
			&& (!ft_strncmp(pipex->exec->cmd[0], "cd", 2)
				|| (!ft_strncmp(pipex->exec->cmd[0], "export", 6)
					&& pipex->exec->cmd[1])
				|| !ft_strncmp(pipex->exec->cmd[0], "unset", 5)))
		{
			lonely_child(data, pipex);
		}
		else if (pipex->exec->in != -1 && pipex->exec->out != -1)
		{
			child(data, pipex);
		}
		close_iofiles_and_free_prev_exec(pipex);
	}
}
