/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 22:49:41 by j_sk8             #+#    #+#             */
/*   Updated: 2024/10/23 15:34:38 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exec(t_data *data, char **env)
{
	data->pid = fork();
	if (data->pid < 0)
	{
		perror("fork");
		free(data->input);
		free_env(data->env);
		exit(EXIT_FAILURE);
	}
	if (data->pid == 0)
	{
		if (data->token->path)
		{
			execve(data->token->path, data->args, env);
			perror("execve");
		}
		else
		{
			printf("Command not found: %s\n", data->args[0]);
		}
		exit(EXIT_FAILURE);
	}
	else
		wait(NULL);
}
