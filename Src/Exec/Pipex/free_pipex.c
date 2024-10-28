/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:56:46 by nsauret           #+#    #+#             */
/*   Updated: 2024/10/28 18:08:53 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	parent_free(t_pipex *pipex)
{
	int	i;

	i = 0;
	// if (pipex->infile)
	// 	close(pipex->infile);
	// if (pipex->outfile)
	// 	close(pipex->outfile);
	if (pipex->here_doc)
		unlink(".heredoc_tmp");
	free(pipex->pipe);
}

void	child_free(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmd_args[i])
	{
		free(pipex->cmd_args[i]);
		i++;
	}
	free(pipex->cmd_args);
	free(pipex->cmd);
	// if (pipex->infile)
	// 	close(pipex->infile);
	// if (pipex->outfile)
	// 	close(pipex->outfile);
}

int	pipe_free(t_pipex *pipex)
{
	if (pipex->here_doc)
		unlink(".heredoc_tmp");
	free(pipex->pipe);
	return (exit_error_pipex(pipex, 0, "Environment"));
}
