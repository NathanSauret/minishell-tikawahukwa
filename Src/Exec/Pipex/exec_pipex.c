/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:11:51 by nathan            #+#    #+#             */
/*   Updated: 2024/11/05 17:42:04 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

// static void	redirection(t_pipex *px, t_data *data, t_cmd *cmd)
// {
// 	if (cmd->infile >= 0)
// 		dup2(cmd->infile, 0);
// 	else if (data->num_of_pipe > 0 && px->idx > 0)
// 		dup2(px->pipe[2 * px->idx - 2], 0);

// 	if (cmd->outfile >= 0)
// 		dup2(cmd->outfile, 1);
// 	else if (data->num_of_pipe > 0 && px->idx < px->cmd_nb - 1)
// 		dup2(px->pipe[2 * px->idx + 1], 1);
// }

// static int	child(t_data *data, t_pipex *px, t_cmd *cmd, char **env)
// {
// 	px->pid = fork();
// 	if (!px->pid)
// 	{
// 		redirection(px, data, cmd);
// 		close_pipes(px, data);
// 		execve(cmd->path, cmd->cmd, env);
// 	}
// 	return (1);
// }

void	exec_pipex(t_pipex *pipex, char **env)
{
	t_exec	*exec;

	exec = pipex->exec;
	(void)env;
	pipex->idx = -1;
	while (++pipex->idx < pipex->cmd_nb)
	{
		ft_printf("cmd in exec_pipex: %S\n", exec->cmd);
		// if (ft_strncmp(cmd->cmd[0], "sleep", 5))
		// 	child(data, pipex, cmd, env);
		exec = exec->next;
	}
	// sleep_case(all, argv, envp);
	return ;
}
