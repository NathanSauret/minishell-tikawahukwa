/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:19:51 by j_sk8             #+#    #+#             */
/*   Updated: 2024/12/05 22:43:36 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	terminate(t_data *data, char *msg, int ext_status)
{
	if (data->pipex)
	{
		close_pipes(data->pipex, data);
		free_child(data, data->pipex);
	}
	free_token(data);
	ft_env_lstclear(&data->env);
	rl_clear_history();
	if (msg)
		ft_printerr(msg);
	exit (ext_status);
}
