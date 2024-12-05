/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:55:14 by nsauret           #+#    #+#             */
/*   Updated: 2024/12/05 14:20:10 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	create_pipes(t_pipex *pipex, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_pipe)
	{
		if (pipe(pipex->pipe + 2 * i) < 0)
			return (free_parent(pipex, data), 0);
		i++;
	}
	return (1);
}

void	close_pipes(t_pipex *pipex, t_data *data)
{
	int	i;

	i = 0;
	while (i < (data->num_of_pipe * 2))
	{
		if (pipex->pipe[i] > -1)
			close(pipex->pipe[i]);
		i++;
	}
}
