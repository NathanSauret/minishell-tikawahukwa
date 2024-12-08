/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:14:06 by nsauret           #+#    #+#             */
/*   Updated: 2024/12/08 23:11:27 by j_sk8            ###   ########.fr       */
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

int	free_pipe(t_pipex *pipex)
{
	free(pipex->pipe);
	return (exit_error_exec(pipex, 0, "Environment"));
}
