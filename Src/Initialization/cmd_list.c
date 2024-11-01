/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:59:26 by j_sk8             #+#    #+#             */
/*   Updated: 2024/10/31 13:56:46 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd	*ft_cmd_lstlast(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_cmd	*ft_cmd_lstnew(char **cmd, int infile, int outfile)
{
	t_cmd	*t_newnode;

	t_newnode = malloc(sizeof(t_cmd));
	if (!t_newnode)
		return (NULL);
	t_newnode->cmd = cmd;
	t_newnode->is_builtin = 0;
	t_newnode->path = NULL;
	t_newnode->infile = infile;
	t_newnode->outfile = outfile;
	t_newnode->next = NULL;
	t_newnode->prev = NULL;
	return (t_newnode);
}

int	ft_cmd_lstadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*tmp;

	if (!lst || !new)
		return (0);
	if (*lst == NULL)
		*lst = new;
	else
	{
		tmp = ft_cmd_lstlast(*(lst));
		tmp->next = new;
		new->prev = tmp;
	}
	return (1);
}

void	ft_cmd_lstclear(t_cmd **lst)
{
	t_cmd	*tmp;

	if (!lst || !(*lst))
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		if ((*lst)->infile > 0)
			close((*lst)->infile);
		if ((*lst)->outfile > 0)
			close((*lst)->outfile);
		free((*lst)->path);
		free((*lst)->cmd);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}
