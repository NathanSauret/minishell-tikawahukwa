/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:20:10 by nsauret           #+#    #+#             */
/*   Updated: 2024/11/01 16:02:48 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static int	get_commands_and_paths(t_pipex *pipex, t_data *data)
{
	int		i;
	t_cmd	*cmd;

	cmd = data->cmd;
	pipex->commands = (char ***)malloc(sizeof(char **) * (pipex->cmd_nb));
	pipex->paths = (char **)malloc(sizeof(char *) * (pipex->cmd_nb));
	pipex->infiles = (int *)malloc(sizeof(int *) * (pipex->cmd_nb));
	pipex->outfiles = (int *)malloc(sizeof(int *) * (pipex->cmd_nb));
	if (!pipex->commands || !pipex->paths
		|| !pipex->infiles || !pipex->outfiles)
		return (0);
	i = 0;
	while (i < pipex->cmd_nb)
	{
		pipex->commands[i] = cmd->cmd;
		pipex->paths[i] = cmd->path;
		pipex->infiles[i] = cmd->infile;
		pipex->outfiles[i] = cmd->outfile;
		cmd = cmd->next;
		i++;
	}
	return (1);
}

static int	set_values(t_pipex *pipex, t_data *data)
{
	pipex->cmd_nb = data->num_of_pipe + 1;
	if (!get_commands_and_paths(pipex, data))
		return (0);
	if (data->num_of_pipe > 0)
	{
		pipex->pipe = (int *)malloc(sizeof(int) * (data->num_of_pipe * 2));
		if (!pipex->pipe)
			return (exit_error_pipex(pipex, 1, "Error: pipe"));
	}
	return (1);
}

int	pipex(t_data *data, char **env)
{
	t_pipex	pipex;

	if (!set_values(&pipex, data))
		return (0);
	create_pipes(&pipex, data);
	exec_pipex(&pipex, data, env);
	close_pipes(&pipex, data);
	waitpid(-1, NULL, 0);
	parent_free(&pipex, data);
	return (1);
}
