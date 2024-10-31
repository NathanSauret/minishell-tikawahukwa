/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 22:49:41 by j_sk8             #+#    #+#             */
/*   Updated: 2024/10/31 14:58:32 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exec_builtin(t_data *data)
{
	if (ft_strnstr((data->token->str), "exit", 4))
		return (ft_exit(data));
	if (ft_strnstr((data->token->str), "cd", 2))
		return (ft_cd(data->args));
	if (ft_strnstr((data->token->str), "echo", 4))
		return (ft_echo(data->args));
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
			execve(data->cmd->path, data->cmd->cmd, env);
			perror("execve");
		}
		else
			printf("Command not found: %s\n", data->cmd->cmd[0]);
		free_token(data);
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
