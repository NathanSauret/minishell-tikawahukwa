/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:56:46 by nsauret           #+#    #+#             */
/*   Updated: 2024/11/07 15:57:20 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"


// static void	free_array(char	**array)
// {
// 	int	i;

// 	i = 0;
// 	while (array[i])
// 		free(array[i++]);
// 	free(array);
// }

static void	exec_free(t_pipex *pipex)
{
	t_exec	*exec;
	t_exec	*prev_exec;

	exec = pipex->exec;
	while (exec)
	{
		if (exec->cmd)
			free(exec->cmd);
		if (exec->path)
			free(exec->path);
		close(exec->in);
		close(exec->out);
		prev_exec = exec;
		exec = exec->next;
		free(prev_exec);
	}
}

void	parent_free(t_pipex *pipex, t_data *data)
{
	int	i;

	i = 0;
	if (pipex->here_doc)
		unlink(".heredoc_tmp");
	if (data->num_of_pipe > 0)
		free(pipex->pipe);
	exec_free(pipex);
}

int	pipe_free(t_pipex *pipex)
{
	if (pipex->here_doc >= 0)
		unlink(".heredoc_tmp");
	free(pipex->pipe);
	return (exit_error_pipex(pipex, 0, "Environment"));
}
