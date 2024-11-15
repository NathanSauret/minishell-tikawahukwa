/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:59:26 by j_sk8             #+#    #+#             */
/*   Updated: 2024/11/08 14:50:02 by nsauret          ###   ########.fr       */
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

t_cmd	*ft_cmd_lstnew(char **cmd)
{
	t_cmd	*t_newnode;

	t_newnode = malloc(sizeof(t_cmd));
	if (!t_newnode)
		return (NULL);
	t_newnode->cmd = cmd;
	t_newnode->is_builtin = 0;
	t_newnode->path = NULL;
	t_newnode->next = NULL;
	t_newnode->prev = NULL;
	t_newnode->tokens = NULL;
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
		(*lst)->tokens = NULL;
		free((*lst)->path);
		free((*lst)->cmd);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}
