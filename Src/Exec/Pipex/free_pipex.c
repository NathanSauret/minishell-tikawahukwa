/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:56:46 by nsauret           #+#    #+#             */
/*   Updated: 2024/11/01 16:01:15 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	parent_free(t_pipex *pipex, t_data *data)
{
	int	i;

	i = 0;
	// if (pipex->here_doc)
	// 	unlink(".heredoc_tmp");
	if (data->num_of_pipe > 0)
		free(pipex->pipe);
	free(pipex->commands);
	free(pipex->paths);
	free(pipex->infiles);
	free(pipex->outfiles);
}

int	pipe_free(t_pipex *pipex)
{
	if (pipex->here_doc >= 0)
		unlink(".heredoc_tmp");
	free(pipex->pipe);
	return (exit_error_pipex(pipex, 0, "Environment"));
}
