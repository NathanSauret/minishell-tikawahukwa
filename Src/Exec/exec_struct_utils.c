/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_struct_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:29:11 by nsauret           #+#    #+#             */
/*   Updated: 2024/12/16 13:22:47 by nsauret          ###   ########.fr       */
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

int	execadd_back(t_exec **exec, t_exec *new)
{
	t_exec	*tmp;

	if (!exec || !new)
		return (0);
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
	return (1);
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
