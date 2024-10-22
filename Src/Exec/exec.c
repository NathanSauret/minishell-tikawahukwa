/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 22:49:41 by j_sk8             #+#    #+#             */
/*   Updated: 2024/10/22 12:58:38 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exec(t_data *data, char **env)
{
	char	*exec_path;

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
		exec_path = get_ex_path(data->args[0], data);
		if (exec_path)
		{
			execve(exec_path, data->args, env);
			perror("execve");
			free(exec_path);
		}
		else
			printf("Command not found: %s\n", data->args[0]);
		exit(EXIT_FAILURE);
	}
	else
		wait(NULL);
}
