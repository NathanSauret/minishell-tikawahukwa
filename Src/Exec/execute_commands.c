/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:11:51 by nathan            #+#    #+#             */
/*   Updated: 2024/11/18 16:02:35 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exec_builtin(t_data *data, t_pipex *pipex)
{
	if (ft_strnstr((pipex->exec->cmd[0]), "exit", 4))
		return (ft_exit(data));
	if (ft_strnstr((pipex->exec->cmd[0]), "cd", 2))
		return (ft_cd(data->env, data->args));
	if (ft_strnstr((pipex->exec->cmd[0]), "echo", 4))
		return (ft_echo(pipex->exec->cmd));
	if (ft_strnstr((data->token->str), "env", 3))
			return (ft_env(data->env));
	 if (ft_strnstr((data->token->str), "export", 6))
	 	return (ft_export(pipex->exec->cmd, data));
	if (ft_strnstr((data->token->str), "pwd", 3))
		return (ft_pwd());
	// if (ft_strnstr((data->token->str), "unset", 5))
	// 	return (ft_unset(data));
	return (-1);
}

static int	child(t_data *data, t_pipex *pipex, char **env)
{
	t_exec	*exec;
	int		res;
	int		status;

	exec = pipex->exec;
	pipex->pid = fork();
	res = 1;
	if (!pipex->pid)
	{
		dup2(exec->in, 0);
		dup2(exec->out, 1);
		close_pipes(pipex, data);
		if (exec->is_builtin)
			res = exec_builtin(data, pipex);
		else
			execve(exec->path, exec->cmd, env);
		if (exec->is_infile)
			close(exec->in);
		if (exec->is_outfile)
			close(exec->out);
		free_token(data);
		free_env(data->env);
		exit (res);
	}
	waitpid(pipex->pid, &status, 0);
	return (WEXITSTATUS (status));
}

int	execute_commands(t_data *data, t_pipex *pipex, char **env)
{
	t_exec	*exec_head;
	int		res;

	exec_head = pipex->exec;
	pipex->idx = -1;
	res = 1;
	while (++pipex->idx < pipex->cmd_nb)
	{
		if (ft_strncmp(pipex->exec->cmd[0], "sleep", 5)
			&& ft_strncmp(pipex->exec->cmd[0], "exit", 4)
			&& pipex->exec->in != -1 && pipex->exec->out != -1)
		{
			res = child(data, pipex, env);
		}
		pipex->exec = pipex->exec->next;
	}
	pipex->exec = exec_head;
	// sleep_case(all, argv, envp);
	return (res);
}
