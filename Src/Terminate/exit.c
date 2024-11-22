/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:19:51 by j_sk8             #+#    #+#             */
/*   Updated: 2024/11/22 18:29:15 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	terminate(t_data *data, char *msg, int ext_status)
{
	free_env(data->env);
	free_token(data);
	if (msg)
		printf("%s", msg);
	exit (ext_status);
}

int	exit_error2(t_data *data, char *str)
{
	printf("%s", str);
	free_env(data->env);
	free_token(data);
	clear_history();
	return (0);
}
