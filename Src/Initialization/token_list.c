/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 20:44:08 by j_sk8             #+#    #+#             */
/*   Updated: 2024/10/25 16:01:44 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*ft_token_lstlast(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_token	*ft_token_lstnew(char *str, int type)
{
	t_token	*t_newnode;

	t_newnode = malloc(sizeof(t_token));
	if (!t_newnode)
		return (NULL);
	t_newnode->str = str;
	t_newnode->path = NULL;
	t_newnode->type = type;
	t_newnode->is_builtin = 0;
	t_newnode->next = NULL;
	t_newnode->prev = NULL;
	return (t_newnode);
}

int	ft_token_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (!lst || !new)
		return (0);
	if (*lst == NULL)
		*lst = new;
	else
	{
		tmp = ft_token_lstlast(*(lst));
		tmp->next = new;
		new->prev = tmp;
	}
	return (1);
}

void	ft_token_lstclear(t_token **lst)
{
	t_token	*tmp;

	if (!lst || !(*lst))
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->str);
		if ((*lst)->path)
			free((*lst)->path);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}
