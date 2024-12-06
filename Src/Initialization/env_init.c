/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:17:13 by jmiccio           #+#    #+#             */
/*   Updated: 2024/12/06 13:12:34 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	copy_shlvl_env(char *res, const char *str, const char *num)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
		{
			k = 0;
			while (num[k])
				res[j++] = num[k++];
			while (ft_isdigit(str[i]))
				i++;
		}
		else
			res[j++] = str[i++];
	}
	res[j] = '\0';
}

static char	*get_new_shlvl(t_data *data, char *str)
{
	int		lvl;
	char	*res;
	int		size;
	int		i;
	char	*num;

	i = 0;
	size = ft_strlen(str);
	if (strchr(str, '9'))
		size++;
	while (str[i] && !ft_isdigit(str[i]))
		i++;
	lvl = ft_atoi(&str[i]);
	lvl++;
	num = ft_itoa(lvl);
	if (!num)
		terminate(data, ERR_MALLOC, 1);
	res = malloc(sizeof(char) + (size + 1));
	if (!res)
		terminate(data, ERR_MALLOC, 1);
	copy_shlvl_env(res, str, num);
	free(num);
	free(str);
	return (res);
}

void	creat_mshlvl(t_data *data)
{
	if (!ft_env_lstadd_back(&data->env,
			ft_env_lstnew(ft_strdup("MSHLVL=1"))))
		terminate(data, ERR_MALLOC, 1);
}

int	shlvl_handler(t_data *data)
{
	t_env	*current;

	current = data->env;
	while (current)
	{
		if (ft_strncmp(current->value, "SHLVL=", 5) == 0)
		{
			current->value = get_new_shlvl(data, current->value);
			break ;
		}
		current = current->next;
	}
	current = data->env;
	while (current)
	{
		if (ft_strncmp(current->value, "MSHLVL=", 6) == 0)
		{
			current->value = get_new_shlvl(data, current->value);
			return (0);
		}
		current = current->next;
	}
	creat_mshlvl(data);
	return (1);
}
