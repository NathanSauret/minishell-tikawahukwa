/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 20:08:19 by jmiccio           #+#    #+#             */
/*   Updated: 2024/12/08 22:13:45 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*ft_env_lstlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_env	*ft_env_lstnew(char *value)
{
	t_env	*t_newnode;

	if (!value)
		return (NULL);
	t_newnode = malloc(sizeof(t_env));
	if (!t_newnode)
		return (NULL);
	t_newnode->next = NULL;
	t_newnode->prev = NULL;
	t_newnode->value = value;
	return (t_newnode);
}

int	ft_env_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!lst || !new)
		return (0);
	if (*lst == NULL)
		*lst = new;
	else
	{
		tmp = ft_env_lstlast(*(lst));
		tmp->next = new;
		new->prev = tmp;
	}
	return (1);
}

void	ft_env_lstclear(t_env **lst)
{
	t_env	*tmp;

	if (!lst || !(*lst))
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		if ((*lst)->value)
			free((*lst)->value);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}
