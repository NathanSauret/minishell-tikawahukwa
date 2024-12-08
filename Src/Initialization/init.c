/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 21:40:17 by j_sk8             #+#    #+#             */
/*   Updated: 2024/12/08 22:14:40 by j_sk8            ###   ########.fr       */
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
	data->pipex = NULL;
	data->env_len = 0;
	data->num_of_pipe = 0;
	data->exit_status = 0;
	data->is_space = 0;
	g_signal_pid = 0;
	signals();
}

int	env_init(t_data *data, char **env_array)
{
	int		i;

	if (!env_array || !env_array[0])
		return (0);
	i = 0;
	while (env_array[i])
	{
		if (!ft_env_lstadd_back(&data->env,
				ft_env_lstnew(ft_strdup(env_array[i]))))
			terminate(data, ERR_MALLOC, 1);
		i++;
	}
	i += shlvl_handler(data);
	return (i);
}
