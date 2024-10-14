/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:15:09 by jmiccio           #+#    #+#             */
/*   Updated: 2024/10/14 21:01:16 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*t_newnode;

	t_newnode = malloc(sizeof(t_list));
	if (!t_newnode)
		return (NULL);
	t_newnode->content = content;
	t_newnode->next = NULL;
	return (t_newnode);
}
