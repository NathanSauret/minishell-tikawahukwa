/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 23:27:39 by j_sk8             #+#    #+#             */
/*   Updated: 2024/11/26 15:19:33 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_command_line(t_token *token)
{
	while (token)
	{
		if (token->command_line)
			free(token->command_line);
		token = token->next;
	}
}

void	free_token(t_data *data)
{
	if (data->input)
		free(data->input);
	if (data->token)
		ft_token_lstclear(&(data->token));
	if (data->cmd)
		ft_cmd_lstclear(&(data->cmd));
	if (data->args)
	{
		free(data->args);
		data->args = NULL;
	}
	data->num_of_pipe = 0;
}

int	is_error(char *str, t_data *data, int exit_status)
{
	data->exit_status = exit_status;
	if (str)
		ft_printerr("%s", str);
	free_token(data);
	return (0);
}
