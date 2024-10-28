/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:20:10 by nsauret           #+#    #+#             */
/*   Updated: 2024/10/28 18:09:10 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static int	set_values(t_pipex *pipex, t_data *data)
{
	// get_infile(arg, all);
	// get_outfile(argv[argc - 1], all);
	pipex->cmd_nb = data->num_of_pipe + 1;
	pipex->pipe = (int *)malloc(sizeof(int) * (data->num_of_pipe + 1));
	if (!pipex->pipe)
		return (exit_error_pipex(pipex, 1, "Error: pipe"));
	return (1);
}

int	pipex(t_data *data, char **env)
{
	t_pipex	pipex;

	(void)env;
	if (!set_values(&pipex, data))
		return (0);
	create_pipes(&pipex, data);
	// exec_pipex(&pipex, data, env);
	close_pipes(&pipex, data);
	waitpid(-1, NULL, 0);
	parent_free(&pipex);
	return (1);
}
