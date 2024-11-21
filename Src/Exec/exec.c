/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:20:10 by nsauret           #+#    #+#             */
/*   Updated: 2024/11/21 15:00:05 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	set_values(t_pipex *pipex, t_data *data)
{
	pipex->cmd_nb = data->num_of_pipe + 1;
	if (data->num_of_pipe > 0)
	{
		pipex->pipe = (int *)malloc(sizeof(int) * (data->num_of_pipe * 2));
		if (!pipex->pipe)
		{
			free_pipe(pipex);
			return (exit_error_exec(pipex, 1, "Error: pipe"));
		}
	}
	pipex->here_doc = 0;
	return (1);
}

int	exec(t_data *data, char **env)
{
	t_pipex	pipex;
	int		res_execute_commands;

	if (!data->num_of_pipe && !ft_strncmp(data->args[0], "exit", 4))
		return (ft_exit(data), -1);
	if (!set_values(&pipex, data))
		return (0);
	if (!create_pipes(&pipex, data))
		return (0);
	prepare_for_exec(data, &pipex);
	res_execute_commands = execute_commands(data, &pipex, env);
	close_pipes(&pipex, data);
	free_parent(&pipex, data);
	waitpid(-1, NULL, 0);
	return (res_execute_commands);
}
