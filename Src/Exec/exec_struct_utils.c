/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_struct_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:29:11 by nsauret           #+#    #+#             */
/*   Updated: 2024/11/29 14:48:06 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_exec	*execnew(t_cmd *cmd, int in, int out)
{
	t_exec	*t_newnode;

	t_newnode = malloc(sizeof(t_exec));
	if (!t_newnode)
		return (NULL);
	t_newnode->cmd = cmd->cmd;
	t_newnode->path = cmd->path;
	t_newnode->is_builtin = cmd->is_builtin;
	t_newnode->in = in;
	t_newnode->out = out;
	t_newnode->is_infile = 0;
	t_newnode->is_outfile = 0;
	t_newnode->next = NULL;
	return (t_newnode);
}

static t_exec	*execlast(t_exec *exec)
{
	if (!exec)
		return (NULL);
	while (exec->next)
		exec = exec->next;
	return (exec);
}

void	execadd_back(t_exec **exec, t_exec *new)
{
	t_exec	*tmp;

	if (!exec || !new)
		return ;
	if (exec)
	{
		if (*exec == NULL)
			*exec = new;
		else
		{
			tmp = execlast(*(exec));
			tmp->next = new;
		}
	}
}
