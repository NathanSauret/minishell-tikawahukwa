/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:11:51 by nathan            #+#    #+#             */
/*   Updated: 2024/11/20 17:50:11 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	exec_builtin(t_data *data, t_pipex *pipex)
{
	if (ft_strnstr((pipex->exec->cmd[0]), "cd", 2))
		return (ft_cd(data->args));
	if (ft_strnstr((pipex->exec->cmd[0]), "echo", 4))
		return (ft_echo(pipex->exec->cmd));
	// if (ft_strnstr((data->token->str), "env", 3))
	// 	return (ft_env(data));
	// if (ft_strnstr((data->token->str), "export", 6))
	// 	return (ft_export(data));
	// if (ft_strnstr((data->token->str), "pwd", 3))
	// 	return (ft_pwd(data));
	// if (ft_strnstr((data->token->str), "unset", 5))
	// 	return (ft_unset(data));
	return (-1);
}

static void	close_iofiles(t_exec *exec)
{
	if (exec->in != 0)
		close(exec->in);
	if (exec->out != 1)
		close(exec->out);
}

static void	free_child(t_data *data, t_pipex *pipex)
{	
	t_exec	*prev_exec;

	while (pipex->exec)
	{
		prev_exec = pipex->exec;
		pipex->exec = pipex->exec->next;
		close_iofiles(prev_exec);
		free(prev_exec);
	}
	free_parent(pipex, data);
	free_token(data);
	free_env(data->env);
}

static int	child(t_data *data, t_pipex *pipex, char **env)
{
	t_exec	*exec;
	int		res;
	int		status;

	data->pid = fork();
	res = -1;
	if (!data->pid)
	{
		exec = pipex->exec;
		dup2(exec->in, 0);
		dup2(exec->out, 1);
		close_pipes(pipex, data);
		if (exec->is_builtin)
			res = exec_builtin(data, pipex);
		else
			res = execve(exec->path, exec->cmd, env);
		free_child(data, pipex);
		exit (res);
	}
	waitpid(data->pid, &status, 0);
	return (WEXITSTATUS (status));
}

int	execute_commands(t_data *data, t_pipex *pipex, char **env)
{
	char	*max_sleep;
	t_exec	*prev_exec;
	int		res;

	max_sleep = "0";
	res = 1;
	while (pipex->exec)
	{
		if (ft_strncmp(pipex->exec->cmd[0], "sleep", 5)
			&& ft_strncmp(pipex->exec->cmd[0], "exit", 4)
			&& pipex->exec->in != -1 && pipex->exec->out != -1)
		{
			res = child(data, pipex, env);
		}
		if (!ft_strncmp(pipex->exec->cmd[0], "sleep", 5)
			&& ft_atoi(pipex->exec->cmd[1]) > ft_atoi(max_sleep))
		{
			max_sleep = pipex->exec->cmd[1];
		}
		prev_exec = pipex->exec;
		pipex->exec = pipex->exec->next;
		close_iofiles(prev_exec);
		free(prev_exec);
	}
	return (sleep_case(max_sleep, env), res);
}
