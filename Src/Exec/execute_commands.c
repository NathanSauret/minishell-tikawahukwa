/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:11:51 by nathan            #+#    #+#             */
/*   Updated: 2024/11/26 17:24:10 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exec_builtin(t_data *data, t_pipex *pipex)
{
	if (ft_strnstr((pipex->exec->cmd[0]), "cd", 2))
		return (ft_cd(data->env, pipex->exec->cmd));
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
	return (-1);
}

static void	close_iofiles_and_free_prev_exec(t_pipex *pipex)
{
	t_exec	*prev_exec;

	prev_exec = pipex->exec;
	pipex->exec = pipex->exec->next;
	if (prev_exec->is_infile)
		close(prev_exec->in);
	if (prev_exec->is_outfile)
		close(prev_exec->out);
	free(prev_exec);
}

static int	lonely_child(t_data *data, t_pipex *pipex)
{
	int		res;

	res = exec_builtin(data, pipex);
	data->exit_status = res;
	return (res);
}

static int	child(t_data *data, t_pipex *pipex)
{
	t_exec	*exec;
	int		res;
	int		status;

	data->pid = fork();
	res = -1;
	if (!data->pid)
	{
		// ft_printf("cmd: %s ~ in: %d | out: %d\n", pipex->exec->cmd[0], pipex->exec->in, pipex->exec->out);
		exec = pipex->exec;
		dup2(exec->in, 0);
		dup2(exec->out, 1);
		// if (exec->is_infile)
		// 	close(exec->in);
		// if (exec->is_outfile)
		// 	close(exec->out);
		close_pipes(pipex, data);
		if (exec->is_builtin)
			res = exec_builtin(data, pipex);
		else
			res = execve(exec->path, exec->cmd, data->env_array);
		free_child(data, pipex);
		exit (res);
	}
	waitpid(data->pid, &status, 0);
	data->exit_status = WEXITSTATUS (status);
	return (WEXITSTATUS (status));
}

int	execute_commands(t_data *data, t_pipex *pipex)
{
	char	*max_sleep;
	int		res;

	max_sleep = "0";
	res = 1;
	while (pipex->exec)
	{
		if (!data->num_of_pipe
			&& (!ft_strncmp(pipex->exec->cmd[0], "cd", 2)
				|| !ft_strncmp(pipex->exec->cmd[0], "export", 6)
				|| !ft_strncmp(pipex->exec->cmd[0], "unset", 5)))
			res = lonely_child(data, pipex);
		else if (ft_strncmp(pipex->exec->cmd[0], "sleep", 5)
			&& ft_strncmp(pipex->exec->cmd[0], "exit", 4)
			&& pipex->exec->in != -1 && pipex->exec->out != -1)
			res = child(data, pipex);
		if (!ft_strncmp(pipex->exec->cmd[0], "sleep", 5)
			&& ft_atoi(pipex->exec->cmd[1]) > ft_atoi(max_sleep))
			max_sleep = pipex->exec->cmd[1];
		close_iofiles_and_free_prev_exec(pipex);
	}
	// sleep_case(max_sleep, env);
	return (res);
}
