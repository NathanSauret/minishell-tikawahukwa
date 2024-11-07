/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_for_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:50:29 by nsauret           #+#    #+#             */
/*   Updated: 2024/11/07 15:08:16 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	create_exec_struct(t_cmd *cmd, t_pipex *pipex)
{
	pipex->exec = execnew(cmd, -2, -2);
	cmd = cmd->next;
	while (cmd)
	{
		execadd_back(&pipex->exec, execnew(cmd, -2, -2));
		cmd = cmd->next;
	}
}

static void	check_redirections(t_cmd *cmd, t_pipex *pipex)
{
	if (cmd->tokens->type == INPUT)
	{
		cmd->tokens = cmd->tokens->next;
		pipex->exec->in = redirection_input(cmd);
	}
	else if (cmd->tokens->type == TRUNC)
	{
		cmd->tokens = cmd->tokens->next;
		pipex->exec->out = redirection_trunc(pipex, cmd);
	}
}

static void	redirect_with_pipes(t_pipex *pipex)
{
	if (pipex->exec->in == -2 && pipex->idx == 0)
		pipex->exec->in = 0;
	else if (pipex->exec->in == -2)
		pipex->exec->in = pipex->pipe[2 * pipex->idx - 2];

	if (pipex->exec->out == -2 && pipex->idx == (pipex->cmd_nb - 1))
		pipex->exec->out = 1;
	if (pipex->exec->out == -2)
		pipex->exec->out = pipex->pipe[2 * pipex->idx + 1];
}

void	prepare_for_exec(t_data *data, t_pipex *pipex)
{
	t_exec	*exec_head;

	create_exec_struct(data->cmd, pipex);
	exec_head = pipex->exec;
	pipex->idx = 0;
	while (pipex->exec)
	{
		if (!pipex->exec->is_builtin)
		{
			while (data->cmd->tokens)
			{
				check_redirections(data->cmd, pipex);
				data->cmd->tokens = data->cmd->tokens->next;
			}
		}
		redirect_with_pipes(pipex);
		data->cmd = data->cmd->next;
		pipex->exec = pipex->exec->next;
		pipex->idx++;
	}
	pipex->exec = exec_head;
}
