/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:14:06 by nsauret           #+#    #+#             */
/*   Updated: 2024/11/21 15:43:17 by nsauret          ###   ########.fr       */
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
