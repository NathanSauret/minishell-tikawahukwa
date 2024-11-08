/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:11:51 by nathan            #+#    #+#             */
/*   Updated: 2024/11/08 15:15:21 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

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
		execve(exec->path, exec->cmd, env);
	}
	return (1);
}

void	exec_pipex(t_data *data, t_pipex *pipex, char **env)
{
	t_exec	*exec_head;

	exec_head = pipex->exec;
	(void)env;
	pipex->idx = -1;
	while (++pipex->idx < pipex->cmd_nb)
	{
		if (ft_strncmp(pipex->exec->cmd[0], "sleep", 5)
			&& pipex->exec->in != -1 && pipex->exec->out != -1)
			child(data, pipex, env);
		pipex->exec = pipex->exec->next;
	}
	pipex->exec = exec_head;
	// sleep_case(all, argv, envp);
}
