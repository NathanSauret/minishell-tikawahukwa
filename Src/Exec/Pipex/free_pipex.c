/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:56:46 by nsauret           #+#    #+#             */
/*   Updated: 2024/11/12 15:57:55 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static void	exec_free(t_pipex *pipex)
{
	t_exec	*exec;
	t_exec	*prev_exec;

	exec = pipex->exec;
	while (exec)
	{
		prev_exec = exec;
		exec = exec->next;
		free(prev_exec);
	}
}

void	parent_free(t_pipex *pipex, t_data *data)
{
	if (pipex->here_doc)
		unlink(".heredoc_tmp");
	if (data->num_of_pipe > 0)
		free(pipex->pipe);
	exec_free(pipex);
}

int	pipe_free(t_pipex *pipex)
{
	if (*pipex->here_doc >= 0)
		unlink(".heredoc_tmp");
	free(pipex->pipe);
	return (exit_error_pipex(pipex, 0, "Environment"));
}
