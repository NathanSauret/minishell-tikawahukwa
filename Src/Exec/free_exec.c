/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:14:06 by nsauret           #+#    #+#             */
/*   Updated: 2024/11/22 16:19:17 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_parent(t_pipex *pipex, t_data *data)
{
	if (pipex->here_doc)
		unlink(".heredoc");
	if (data->num_of_pipe > 0)
		free(pipex->pipe);
}

void	free_child(t_data *data, t_pipex *pipex)
{
	t_exec	*prev_exec;

	while (pipex->exec)
	{
		prev_exec = pipex->exec;
		pipex->exec = pipex->exec->next;
		if (prev_exec->in != 0)
			close(prev_exec->in);
		if (prev_exec->out != 1)
			close(prev_exec->out);
		free(prev_exec);
	}
	free_parent(pipex, data);
	free_token(data);
	free_env(data->env);
}

int	free_pipe(t_pipex *pipex)
{
	if (pipex->here_doc != NULL)
		unlink(".heredoc");
	free(pipex->pipe);
	return (exit_error_exec(pipex, 0, "Environment"));
}
