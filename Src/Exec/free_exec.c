/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:56:46 by nsauret           #+#    #+#             */
<<<<<<< HEAD:Src/Exec/Pipex/free_pipex.c
/*   Updated: 2024/11/12 15:57:55 by j_sk8            ###   ########.fr       */
=======
/*   Updated: 2024/11/11 16:44:54 by nsauret          ###   ########.fr       */
>>>>>>> 422295f (added '>>' redirection, fixed redirections AND pipes problem, partially fixed opened fds problems, restructured the exec code, added builtin use in cmds):Src/Exec/free_exec.c
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	exec_free(t_pipex *pipex)
{
	t_exec	*exec;
	t_exec	*prev_exec;

	exec = pipex->exec;
	while (exec)
	{
		if (exec->is_infile)
			close(exec->in);
		if (exec->is_outfile)
			close(exec->out);
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
	return (exit_error_exec(pipex, 0, "Environment"));
}
