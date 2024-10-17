/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 20:44:08 by j_sk8             #+#    #+#             */
/*   Updated: 2024/10/17 23:03:03 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*ft_token_lstlast(t_token *lst)
{
	t_token	*head;

	if (!lst)
		return (NULL);
	head = lst;
	while (lst->next != head)
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
	t_newnode->type = type;
	t_newnode->next = NULL;
	t_newnode->prev = NULL;

	return (t_newnode);
}

int	ft_token_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (!lst || !new)
		return (0);
	if (lst)
	{
		if (*lst == NULL)
		{
			*lst = new;
			new->next = new;
			new->prev = new;
		}
		else
		{
			tmp = ft_token_lstlast(*(lst));
			tmp->next = new;
			new->prev = tmp;
			new->next = *lst;
			(*lst)->prev = new;
		}
	}
	return (1);
}

void	ft_token_lstclear(t_token **lst)
{
	t_token	*tmp;
	t_token	*head;

	if (!lst || !(*lst))
		return ;
	head = *lst;
	while (*lst != head)
	{
		tmp = (*lst)->next;
		free((*lst)->str);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}
