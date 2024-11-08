/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:20:10 by nsauret           #+#    #+#             */
/*   Updated: 2024/11/07 13:54:39 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static int	set_values(t_pipex *pipex, t_data *data)
{
	pipex->cmd_nb = data->num_of_pipe + 1;
	if (data->num_of_pipe > 0)
	{
		pipex->pipe = (int *)malloc(sizeof(int) * (data->num_of_pipe * 2));
		if (!pipex->pipe)
		{
			pipe_free(pipex);
			return (exit_error_pipex(pipex, 1, "Error: pipe"));
		}
	}
	pipex->here_doc = 0;
	return (1);
}

int	pipex(t_data *data, char **env)
{
	t_pipex	pipex;

	if (!set_values(&pipex, data))
		return (0);
	create_pipes(&pipex, data);
	prepare_for_exec(data, &pipex);
	exec_pipex(data, &pipex, env);
	close_pipes(&pipex, data);
	waitpid(-1, NULL, 0);
	parent_free(&pipex, data);
	return (1);
}
