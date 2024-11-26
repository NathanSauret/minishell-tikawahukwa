/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 21:40:17 by j_sk8             #+#    #+#             */
/*   Updated: 2024/11/26 17:19:34 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	data_init(t_data *data)
{
	data->token = NULL;
	data->input = NULL;
	data->env = NULL;
	data->cmd = NULL;
	data->env_array = NULL;
	data->env_len = 0;
	data->num_of_pipe = 0;
	data->exit_status = 0;
	g_signal_pid = 0;
	signals();
}

int	env_init(t_data *data, char **env_array)
{
	t_env	*env;
	t_env	*new;
	int		i;

	env = malloc(sizeof(t_env));
	if (!env)
		return (0);
	env->value = ft_strdup(env_array[0]);
	env->next = NULL;
	env->prev = NULL;
	data->env = env;
	i = 1;
	while (env_array && env_array[0] && env_array[i])
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return (0);
		new->value = ft_strdup(env_array[i]);
		new->next = NULL;
		new->prev = env;
		env->next = new;
		env = new;
		i++;
	}
	return (i);
}
