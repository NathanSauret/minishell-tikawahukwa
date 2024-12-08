/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:03:55 by nsauret           #+#    #+#             */
/*   Updated: 2024/12/08 15:20:24 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_file_already_in_cmd(t_cmd cmd, char *file)
{
	t_cmd	*new_cmd;

	new_cmd = &cmd;
	new_cmd->tokens = new_cmd->tokens->prev;
	while (new_cmd)
	{
		while (new_cmd->tokens)
		{
			if (ft_strlen(new_cmd->tokens->str) == ft_strlen(file)
				&& !ft_strncmp(new_cmd->tokens->str, file, ft_strlen(file)))
			{
				return (1);
			}
			new_cmd->tokens = new_cmd->tokens->prev;
		}
		new_cmd = new_cmd->prev;
	}
	return (0);
}

int	redirection_input(t_data *data, t_pipex *pipex, t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->tokens->str, O_RDONLY);
	if (fd < 0)
	{
		if (!is_file_already_in_cmd(*cmd, cmd->tokens->str))
			perror(cmd->tokens->str);
		if (!pipex->exec->next)
			data->exit_status = 1;
		return (-1);
	}
	return (fd);
}

int	redirection_trunc(t_data *data, t_pipex *pipex, t_cmd *cmd)
{
	int	fd;

	if (pipex->exec->out != -2)
		close(pipex->exec->out);
	if (!ft_strncmp(cmd->tokens->str, "/dev/stdin", MAX_PATH_LENGTH))
		pipex->exec->is_stdin = 1;
	else
		pipex->exec->is_stdin = 0;
	fd = open(cmd->tokens->str, O_CREAT | O_RDWR | O_TRUNC, 0000644);
	if (fd < 0)
	{
		if (!is_file_already_in_cmd(*cmd, cmd->tokens->str))
			perror(cmd->tokens->str);
		if (!pipex->exec->next)
			data->exit_status = 1;
		return (-1);
	}
	return (fd);
}

int	redirection_append(t_data *data, t_pipex *pipex, t_cmd *cmd)
{
	int	fd;

	if (pipex->exec->out != -2)
		close(pipex->exec->out);
	if (!ft_strncmp(cmd->tokens->str, "/dev/stdin", MAX_PATH_LENGTH))
		pipex->exec->is_stdin = 1;
	else
		pipex->exec->is_stdin = 0;
	fd = open(cmd->tokens->str, O_CREAT | O_RDWR | O_APPEND, 0000644);
	if (fd < 0)
	{
		if (!is_file_already_in_cmd(*cmd, cmd->tokens->str))
			perror(cmd->tokens->str);
		if (!pipex->exec->next)
			data->exit_status = 1;
		return (-1);
	}
	return (fd);
}
