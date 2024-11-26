/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 23:27:38 by j_sk8             #+#    #+#             */
/*   Updated: 2024/11/26 16:57:39 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	absolute_path(char **path, char *cmd, t_data *data)
{
	*path = ft_strdup(cmd);
	if (!(*path))
		terminate(data, ERR_MALLOC, 1);
	if (access((*path), F_OK))
	{
		write(2, (*path), ft_strlen((*path)));
		write(2, " : command not found\n", 21);
		free(*path);
		*path = NULL;
	}
}

int	check_quote(t_data *data, char *str)
{
	int	q;
	int	dq;

	q = -1;
	dq = -1;
	while (*str)
	{
		if (*str == '"' && (q != 1))
			dq = -dq;
		else if (*str == '\'' && (dq != 1))
			q = -q;
		str++;
	}
	if (q == -1 && dq == -1)
		return (1);
	data->exit_status = 2;
	return (0);
}

int	line_is_empty(char *str)
{
	while (*str)
	{
		if (!(ft_is_space(*str)))
			return (0);
		str++;
	}
	return (1);
}

static char	*get_path_from_env(t_data *data)
{
	t_env	*current;

	current = data->env;
	while (current)
	{
		if (ft_strncmp(current->value, "PATH=", 5) == 0)
			return (ft_strdup(current->value + 5));
		current = current->next;
	}
	return (NULL);
}

char	*get_ex_path(char *cmd, t_data *data)
{
	char	*path_var;
	char	full_path[MAX_PATH_LENGTH];
	char	*start;
	char	*end;

	full_path[MAX_PATH_LENGTH - 1] = '\0';
	path_var = get_path_from_env(data);
	start = path_var;
	while (start && *start)
	{
		end = ft_strchr(start, ':');
		if (end)
			*end = '\0';
		ft_strlcpy(full_path, start, MAX_PATH_LENGTH);
		ft_strlcat(full_path, "/", MAX_PATH_LENGTH);
		ft_strlcat(full_path, cmd, MAX_PATH_LENGTH);
		if (access(full_path, X_OK) == 0)
			return (free(path_var), ft_strdup(full_path));
		if (end)
			start = end + 1;
		else
			break ;
	}
	return (free(path_var), NULL);
}
