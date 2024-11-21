/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:56:46 by nsauret           #+#    #+#             */
/*   Updated: 2024/11/21 14:58:10 by nathan           ###   ########.fr       */
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

int	free_pipe(t_pipex *pipex)
{
	if (pipex->here_doc != NULL)
		unlink(".heredoc");
	free(pipex->pipe);
	return (exit_error_exec(pipex, 0, "Environment"));
}
