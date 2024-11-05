/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_for_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:50:29 by nsauret           #+#    #+#             */
/*   Updated: 2024/11/05 17:45:34 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	create_exec_struct(t_cmd *cmd, t_pipex *pipex)
{
	pipex->exec = execnew(cmd, -2, -2);
	cmd = cmd->next;
	while (cmd)
	{
		// use pipex->exec
		execadd_back(pipex->exec, execnew(cmd, -2, -2));
		cmd = cmd->next;
	}
}

static void	check_redirections(t_cmd *cmd, t_pipex *pipex)
{
	if (cmd->tokens->type == 1)
	{
		cmd->tokens = cmd->tokens->next;
		pipex->exec->in = redirection_infile(cmd);
	}
}

void	prepare_for_exec(t_data *data, t_pipex *pipex)
{
	t_exec	*exec;
	t_exec	*exec_head;
	t_cmd	*cmd;

	exec = pipex->exec;
	cmd = data->cmd;
	create_exec_struct(cmd, exec);
	ft_printf("in prepare: %d\n", exec->is_builtin);
	exec_head = exec;
	while (exec)
	{
		if (!exec->is_builtin)
		{
			while (cmd->tokens)
			{
				check_redirections(cmd, exec);
				cmd->tokens = cmd->tokens->next;
			}
		}
		cmd = cmd->next;
		exec = exec->next;
	}
	pipex->exec = exec_head;
}
