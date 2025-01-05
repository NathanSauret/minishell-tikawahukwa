/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:55:14 by nsauret           #+#    #+#             */
/*   Updated: 2025/01/05 23:12:28 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	create_pipes(t_pipex *pipex, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_pipe)
	{
		if (pipe(pipex->pipe + 2 * i) < 0)
		{
			free_parent(pipex, data);
			terminate(data, ERR_PIPE, 1);
		}
		i++;
	}
}

void	close_pipes(t_pipex *pipex, t_data *data)
{
	int	i;

	if (!pipex->pipe)
		return ;
	i = 0;
	while (i < (data->num_of_pipe * 2))
	{
		if (!pipex->pipe[i])
			return ;
		if (pipex->pipe[i] > -1)
			close(pipex->pipe[i]);
		i++;
	}
}
