/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 21:40:17 by j_sk8             #+#    #+#             */
/*   Updated: 2024/10/22 13:02:12 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	data_init(t_data *data)
{
	data->args = NULL;
	data->token = NULL;
	data->input = NULL;
	data->env = NULL;
}

int	env_init(t_data *data, char **env_array)
{
	t_env	*env;
	t_env	*new;
	int		i;

	env = malloc(sizeof(t_env));
	if (!env)
		return (1);
	env->value = ft_strdup(env_array[0]);
	env->next = NULL;
	data->env = env;
	i = 1;
	while (env_array && env_array[0] && env_array[i])
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return (1);
		new->value = ft_strdup(env_array[i]);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	return (0);
}
