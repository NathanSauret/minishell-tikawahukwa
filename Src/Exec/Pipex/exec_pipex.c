/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:11:51 by nathan            #+#    #+#             */
/*   Updated: 2024/11/01 15:57:43 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static void	redirection(t_pipex *px, t_data *data)
{
	if (px->infiles[px->idx] >= 0)
		dup2(px->infiles[px->idx], 0);
	else if (data->num_of_pipe > 0 && px->idx > 0)
		dup2(px->pipe[2 * px->idx - 2], 0);

	if (px->outfiles[px->idx] >= 0)
		dup2(px->outfiles[px->idx], 1);
	else if (data->num_of_pipe > 0 && px->idx < px->cmd_nb - 1)
		dup2(px->pipe[2 * px->idx + 1], 1);
}

static int	child(t_data *data, t_pipex *px, char **env)
{
	px->pid = fork();
	if (!px->pid)
	{
		redirection(px, data);
		close_pipes(px, data);
		execve(px->paths[px->idx], px->commands[px->idx], env);
	}
	return (1);
}

void	exec_pipex(t_pipex *pipex, t_data *data, char **env)
{
	pipex->idx = -1;
	while (++pipex->idx < pipex->cmd_nb)
	{
		if (ft_strncmp(pipex->commands[0][0], "sleep", 5))
		{
			child(data, pipex, env);
		}
	}
	// sleep_case(all, argv, envp);
	return ;
}
