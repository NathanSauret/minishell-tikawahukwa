/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 22:49:41 by j_sk8             #+#    #+#             */
/*   Updated: 2024/10/18 23:01:18 by j_sk8            ###   ########.fr       */
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
		exec_path = get_ex_path(data->arg[0], data);
		if (exec_path)
		{
			execve(exec_path, data->arg, env);
			perror("execve");
			free(exec_path);
		}
		else
			fprintf(stderr, "Command not found: %s\n", data->arg[0]);
		exit(EXIT_FAILURE);
	}
	else
		wait(NULL);
}
