/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_jeremy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 22:49:41 by j_sk8             #+#    #+#             */
/*   Updated: 2024/10/28 15:21:26 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exec_builtin(t_data *data)
{
	if (ft_strnstr((data->token->str), "exit", 4))
		return (ft_exit(data));
	return (1);
}

void	exec_cmd(t_data *data, char **env)
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
			printf("Command not found: %s\n", data->args[0]);
		exit(EXIT_FAILURE);
	}
	else
		wait(NULL);
}

int	exec(t_data *data, char **env)
{
	if (data->token->is_builtin)
		return (exec_builtin(data));
	else
		exec_cmd(data, env);
	return (1);
}
