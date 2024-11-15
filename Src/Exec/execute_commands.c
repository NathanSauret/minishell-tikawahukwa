/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:11:51 by nathan            #+#    #+#             */
/*   Updated: 2024/11/11 17:29:57 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	exec_builtin(t_data *data, t_pipex *pipex)
{
	if (ft_strnstr((pipex->exec->cmd[0]), "exit", 4))
	{
		return (ft_printf("exit\n"), 0);
		return (ft_exit(data));
	}
	if (ft_strnstr((pipex->exec->cmd[0]), "cd", 2))
		return (ft_cd(data->args));
	if (ft_strnstr((pipex->exec->cmd[0]), "echo", 4))
		return (ft_echo(pipex->exec->cmd));
	// if (ft_strnstr((data->token->str), "env", 3))
	// 	return (ft_env(data));
	// if (ft_strnstr((data->token->str), "env", 3))
	// 	return (ft_env(data));
	// if (ft_strnstr((data->token->str), "export", 6))
	// 	return (ft_export(data));
	// if (ft_strnstr((data->token->str), "pwd", 3))
	// 	return (ft_pwd(data));
	// if (ft_strnstr((data->token->str), "unset", 5))
	// 	return (ft_unset(data));
	// ft_printf("YOU FORGOT A F*CKING BUILTIN FUNCTION, YOU DUMBA**!\n");
	return (-1);
}

static int	child(t_data *data, t_pipex *pipex, char **env)
{
	t_exec	*exec;

	exec = pipex->exec;
	pipex->pid = fork();
	if (!pipex->pid)
	{
		dup2(exec->in, 0);
		dup2(exec->out, 1);
		close_pipes(pipex, data);
		if (exec_builtin(data, pipex) == -1)
			execve(exec->path, exec->cmd, env);
		if (exec->is_infile)
			close(exec->in);
		if (exec->is_outfile)
			close(exec->out);
		exit (0);
	}
	if (ft_strnstr((exec->cmd[0]), "exit", 4))
		return (0);
	return (1);
}

int	execute_commands(t_data *data, t_pipex *pipex, char **env)
{
	t_exec	*exec_head;

	exec_head = pipex->exec;
	(void)env;
	pipex->idx = -1;
	while (++pipex->idx < pipex->cmd_nb)
	{
		if (ft_strncmp(pipex->exec->cmd[0], "sleep", 5)
			&& pipex->exec->in != -1 && pipex->exec->out != -1)
		{
			if (!child(data, pipex, env))
			{
				pipex->exec = exec_head;
				return (0);
			}
		}
		pipex->exec = pipex->exec->next;
	}
	pipex->exec = exec_head;
	// sleep_case(all, argv, envp);
	return (1);
}
