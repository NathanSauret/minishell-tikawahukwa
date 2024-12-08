/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_struct_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:29:11 by nsauret           #+#    #+#             */
/*   Updated: 2024/12/08 23:12:08 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	close_iofiles_and_free_prev_exec(t_pipex *pipex)
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

t_exec	*execnew(t_cmd *cmd, int in, int out)
{
	t_exec	*t_newnode;

	t_newnode = malloc(sizeof(t_exec));
	if (!t_newnode)
		return (NULL);
	t_newnode->cmd = cmd->cmd;
	t_newnode->path = NULL;
	t_newnode->in = in;
	t_newnode->out = out;
	t_newnode->is_infile = 0;
	t_newnode->is_outfile = 0;
	t_newnode->is_builtin = 0;
	t_newnode->is_stdin = 0;
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

void	ft_exec_lstclear(t_exec **lst)
{
	t_exec	*tmp;

	if (!lst || !(*lst))
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}
