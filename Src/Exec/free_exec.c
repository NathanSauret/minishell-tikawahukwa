/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:14:06 by nsauret           #+#    #+#             */
/*   Updated: 2024/12/10 15:55:44 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_parent(t_pipex *pipex, t_data *data)
{
	if (data->num_of_pipe > 0 && pipex->pipe != NULL)
	{
		free(pipex->pipe);
		pipex->pipe = NULL;
	}
	if (pipex->exec)
		ft_exec_lstclear(&pipex->exec);
}

void	free_child(t_data *data, t_pipex *pipex)
{
	t_exec	*prev_exec;

	if (pipex)
	{
		while (pipex->exec)
		{
			prev_exec = pipex->exec;
			pipex->exec = pipex->exec->next;
			if (prev_exec->path)
				free(prev_exec->path);
			close(prev_exec->in);
			close(prev_exec->out);
			free(prev_exec);
		}
		free_parent(pipex, data);
	}
}
