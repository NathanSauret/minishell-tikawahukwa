/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 23:27:39 by j_sk8             #+#    #+#             */
/*   Updated: 2024/12/10 16:17:26 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_token(t_data *data)
{
	if (data->env_array)
	{
		free(data->env_array);
		data->env_array = NULL;
	}
	if (data->input)
	{
		free(data->input);
		data->input = NULL;
	}
	if (data->token)
		ft_token_lstclear(&(data->token));
	if (data->cmd)
		ft_cmd_lstclear(&(data->cmd));
	data->pipex = NULL;
	data->token = NULL;
	data->cmd = NULL;
	data->num_of_pipe = 0;
}

int	is_error(char *str, t_data *data, int exit_status)
{
	data->exit_status = exit_status;
	if (str)
	{
		ft_printerr("~ Tikawahukwa ");
		ft_printerr("%s", str);
	}
	free_token(data);
	return (0);
}
