/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_for_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:50:29 by nsauret           #+#    #+#             */
/*   Updated: 2024/12/10 15:56:31 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	create_exec_struct(t_data *data, t_pipex *pipex, t_cmd *cmd)
{
	t_exec	*new_exec;

	pipex->exec = execnew(cmd, -2, -2);
	if (!pipex->exec)
	{
		free_parent(pipex, data);
		terminate(data, ERR_MALLOC, 1);
	}
	cmd = cmd->next;
	while (cmd)
	{
		new_exec = execnew(cmd, -2, -2);
		if (!new_exec)
		{
			free_parent(pipex, data);
			terminate(data, ERR_MALLOC, 1);
		}
		if (!execadd_back(&pipex->exec, new_exec))
		{
			free_parent(pipex, data);
			terminate(data, ERR_MALLOC, 1);
		}
		cmd = cmd->next;
	}
}

static void	check_redirections(t_data *data, t_cmd *cmd, t_pipex *pipex)
{
	if (cmd->tokens->type == INPUT)
	{
		cmd->tokens = cmd->tokens->next;
		pipex->exec->in = redirection_input(data, pipex, cmd);
		pipex->exec->is_infile = 1;
	}
	else if (cmd->tokens->type == HEREDOC)
	{
		cmd->tokens = cmd->tokens->next;
		pipex->exec->in = here_doc(data, cmd->tokens->str);
		pipex->exec->is_infile = 1;
	}
	else if (cmd->tokens->type == TRUNC)
	{
		cmd->tokens = cmd->tokens->next;
		pipex->exec->out = redirection_trunc(data, pipex, cmd);
		pipex->exec->is_outfile = 1;
	}
	else if (cmd->tokens->type == APPEND)
	{
		cmd->tokens = cmd->tokens->next;
		pipex->exec->out = redirection_append(data, pipex, cmd);
		pipex->exec->is_outfile = 1;
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
	else if (pipex->exec->out == -2)
		pipex->exec->out = pipex->pipe[2 * pipex->idx + 1];
}

void	prepare_for_exec(t_data *data, t_pipex *pipex)
{
	t_exec	*exec_head;
	t_cmd	*cmd_head;

	cmd_head = data->cmd;
	create_exec_struct(data, pipex, data->cmd);
	exec_head = pipex->exec;
	pipex->idx = 0;
	while (pipex->exec)
	{
		while (data->cmd->tokens && data->cmd->tokens->type != PIPE)
		{
			if (pipex->exec->in != -1 && pipex->exec->out != -1)
				check_redirections(data, data->cmd, pipex);
			data->cmd->tokens = data->cmd->tokens->next;
		}
		redirect_with_pipes(pipex);
		data->cmd = data->cmd->next;
		pipex->exec = pipex->exec->next;
		pipex->idx++;
	}
	pipex->exec = exec_head;
	data->cmd = cmd_head;
}
