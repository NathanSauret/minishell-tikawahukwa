/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:55:14 by nsauret           #+#    #+#             */
/*   Updated: 2024/11/18 17:04:09 by nsauret          ###   ########.fr       */
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
		close(pipex->pipe[i++]);
}
