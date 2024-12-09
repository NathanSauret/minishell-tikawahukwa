/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 15:26:48 by jmiccio           #+#    #+#             */
/*   Updated: 2024/12/09 10:55:50 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_builtin(char *str)
{
	if (!(ft_strncmp("exit", str, MAX_LENGTH)))
		return (1);
	else if (!(ft_strncmp("cd", str, MAX_LENGTH)))
		return (1);
	else if (!(ft_strncmp("echo", str, MAX_LENGTH)))
		return (1);
	else if (!(ft_strncmp("env", str, MAX_LENGTH)))
		return (1);
	else if (!(ft_strncmp("export", str, MAX_LENGTH)))
		return (1);
	else if (!(ft_strncmp("unset", str, MAX_LENGTH)))
		return (1);
	else if (!(ft_strncmp("pwd", str, MAX_LENGTH)))
		return (1);
	return (0);
}

static void	absolute_path(t_data *data, char **path, char *cmd)
{
	struct stat	sb;

	*path = ft_strdup(cmd);
	if (!(*path))
		terminate(data, ERR_MALLOC, 1);
	if (stat(*path, &sb) == -1)
	{
		ft_printerr("~ Tikawahukwa: %s : No such file or directory\n", *path);
		free(*path);
		terminate(data, NULL, 127);
	}
	if (S_ISDIR(sb.st_mode))
	{
		ft_printerr("~ Tikawahukwa: %s : Is a directory\n", *path);
		free(*path);
		terminate(data, NULL, 126);
	}
	if (access(*path, X_OK) == -1)
	{
		ft_printerr("~ Tikawahukwa: %s : Permission denied\n", *path);
		free(*path);
		terminate(data, NULL, 126);
	}
}

static void	get_path_from_env(t_data *data, char **path, char *cmd)
{
	t_env	*current;
	char	*res;

	res = NULL;
	current = data->env;
	while (current)
	{
		if (ft_strncmp(current->value, "PATH=", 5) == 0)
		{
			res = ft_strdup(current->value + 5);
			if (!res)
				terminate (data, ERR_MALLOC, 1);
			*path = res;
			return ;
		}
		current = current->next;
	}
	ft_printerr("~ Tikawahukwa: %s : command not found\n", cmd);
	terminate(data, NULL, 127);
}

static char	*get_ex_path(char *cmd, t_data *data)
{
	char	*path_var;
	char	full_path[MAX_LENGTH];
	char	*start;
	char	*end;

	get_path_from_env(data, &path_var, cmd);
	start = path_var;
	while (start && *start)
	{
		end = ft_strchr(start, ':');
		if (end)
			*end = '\0';
		ft_strlcpy(full_path, start, MAX_LENGTH);
		ft_strlcat(full_path, "/", MAX_LENGTH);
		ft_strlcat(full_path, cmd, MAX_LENGTH);
		if (access(full_path, X_OK) == 0)
			return (free(path_var), ft_strdup(full_path));
		if (end)
			start = end + 1;
		else
			break ;
	}
	free(path_var);
	ft_printerr("~ Tikawahukwa: %s : command not found\n", cmd);
	return (terminate(data, NULL, 127), NULL);
}

int	check_valid_cmd(t_data *data, t_exec *exec)
{
	char	*path;

	path = NULL;
	if (line_is_empty(exec->cmd[0]))
	{
		ft_printerr("~ Tikawahukwa: %s : command not found\n", exec->cmd[0]);
		terminate(data, NULL, 127);
	}
	if (is_builtin(exec->cmd[0]))
		exec->is_builtin = 1;
	else if (ft_strchr(exec->cmd[0], '/'))
		absolute_path(data, &path, exec->cmd[0]);
	else if (!(ft_strchr(exec->cmd[0], '/')) && !exec->is_builtin)
	{
		path = get_ex_path(exec->cmd[0], data);
		if (!path)
			terminate(data, ERR_MALLOC, 1);
	}
	exec->path = path;
	return (1);
}
