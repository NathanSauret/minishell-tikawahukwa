/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:55:01 by j_sk8             #+#    #+#             */
/*   Updated: 2024/12/11 11:52:28 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	syntax_parsing(char *str)
{
	int	i;

	i = 0;
	if (str[i] && (!ft_isalpha(str[i]) && str[i] != '_'))
		return (0);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

t_env	*exist(t_env *env, char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	while (env)
	{
		if (!ft_strncmp(env->value, str, i)
			&& (env->value[i] == '=' || env->value[i] == '\0'))
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	unset(t_data *data, char *arg)
{
	t_env	*env;
	t_env	*prev;
	t_env	*next;

	prev = NULL;
	next = NULL;
	env = exist(data->env, arg);
	if (!env)
		return ;
	prev = env->prev;
	next = env->next;
	if (prev)
		prev->next = next;
	else if (!prev)
		data->env = next;
	if (next)
		next->prev = prev;
	free(env->value);
	free(env);
	data->env_len -= 1;
}

int	ft_unset(char **arg, t_data *data)
{
	int	i;

	i = 1;
	if (!arg || !arg[i])
		return (0);
	while (arg[i])
	{
		if (!(syntax_parsing(arg[i])))
		{
			i++;
			continue ;
		}
		unset(data, arg[i]);
		i++;
	}
	return (0);
}
