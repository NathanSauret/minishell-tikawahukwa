/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:55:14 by nsauret           #+#    #+#             */
/*   Updated: 2024/11/05 17:10:24 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	create_pipes(t_pipex *pipex, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_pipe)
	{
		if (pipe(pipex->pipe + 2 * i) < 0)
			return (parent_free(pipex, data), 0);
		i++;
	}
	return (1);
}

void	close_pipes(t_pipex *pipex, t_data *data)
{
	int	i;

	i = 0;
	while (i < (data->num_of_pipe))
		close(pipex->pipe[i++]);
}
