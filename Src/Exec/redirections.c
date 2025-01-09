/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:03:55 by nsauret           #+#    #+#             */
/*   Updated: 2025/01/07 14:56:41 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	redirect_std(t_pipex *pipex, t_cmd *cmd, int is_input)
{
	if (!ft_strncmp(cmd->tokens->str, "/dev/stdin", MAX_LENGTH))
	{
		if (pipex->exec->in > -1)
			return (dup(pipex->exec->in));
		if (pipex->idx == 0)
			return (dup(0));
		return (dup(pipex->pipe[2 * pipex->idx - 2]));
	}
	if (!ft_strncmp(cmd->tokens->str, "/dev/stdout", MAX_LENGTH))
	{
		if (pipex->exec->out > -1)
			return (dup(pipex->exec->out));
		if (!pipex->exec->next)
			return (dup(1));
		if (is_input && pipex->idx == 0)
			return (dup(0));
		return (dup(pipex->pipe[2 * pipex->idx + 1]));
	}
	return (-2);
}

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

	fd = redirect_std(pipex, cmd, 1);
	if (fd == -1)
	{
		ft_printerr("dup error\n");
		if (!pipex->exec->next)
			data->exit_status = 1;
		return (-1);
	}
	else if (fd != -2)
		return (pipex->exec->is_infile = 1, fd);
	fd = open(cmd->tokens->str, O_RDONLY);
	if (fd < 0)
	{
		if (!is_file_already_in_cmd(*cmd, cmd->tokens->str))
			perror(cmd->tokens->str);
		if (!pipex->exec->next)
			data->exit_status = 1;
		return (-1);
	}
	return (pipex->exec->is_infile = 1, fd);
}

int	redirection_trunc(t_data *data, t_pipex *pipex, t_cmd *cmd)
{
	int	fd;

	fd = redirect_std(pipex, cmd, 0);
	if (pipex->exec->out > -1)
		close(pipex->exec->out);
	if (fd == -1)
	{
		ft_printerr("dup error\n");
		if (!pipex->exec->next)
			data->exit_status = 1;
		return (-1);
	}
	else if (fd != -2)
		return (fd);
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

	fd = redirect_std(pipex, cmd, 0);
	if (pipex->exec->out > -1)
		close(pipex->exec->out);
	if (fd == -1)
	{
		ft_printerr("dup error\n");
		if (!pipex->exec->next)
			data->exit_status = 1;
		return (-1);
	}
	else if (fd != -2)
		return (fd);
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
