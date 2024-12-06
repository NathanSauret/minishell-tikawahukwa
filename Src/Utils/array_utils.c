/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:38:49 by reldnah           #+#    #+#             */
/*   Updated: 2024/12/06 15:05:00 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**lst_to_arr(t_env *env, int len)
{
	t_env	*lst;
	char	**dest;
	int		i;

	dest = NULL;
	i = 0;
	lst = env;
	dest = (char **)malloc(sizeof(char *) * (len + 1));
	if (!dest)
		return (NULL);
	dest[i] = (lst->value);
	lst = lst->next;
	i++;
	while (lst != NULL)
	{
		dest[i] = (lst->value);
		lst = lst->next;
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

static void	ft_swap_str_tab(int i, int j, char **tab)
{
	char	*temp;

	temp = tab[i];
	tab[i] = tab[j];
	tab[j] = temp;
}

void	sort_array(char **arr, int len)
{
	int	i;
	int	j;
	int	diff;

	i = 0;
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			diff = ft_strncmp(arr[i], arr[j], __INT_MAX__);
			if (diff > 0)
			{
				ft_swap_str_tab(i, j, arr);
				continue ;
			}
			j++;
		}
		i++;
	}
}
