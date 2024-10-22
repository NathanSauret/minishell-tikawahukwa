/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 23:27:38 by j_sk8             #+#    #+#             */
/*   Updated: 2024/10/22 14:20:16 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_quote(char *str)
{
	int	q;
	int	dq;

	q = 0;
	dq = 0;
	while (*str)
	{
		if (*str == '"' && (dq != 1 && q != 1))
		{
			str++;
			dq = 1;
		}
		else if (*str == '\'' && (dq != 1 && q != 1))
		{
			str++;
			q = 1;
		}
		else if ((*str == '\'' && q == 1) || (*str == '"' && dq == 1))
			return (1);
		str++;
	}
	if (q == 0 && dq == 0)
		return (1);
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

int	is_quote(char c)
{
	return ((c == '\'' || c == '"'));
}

char	*get_path_from_env(t_data *data)
{
	t_env	*current;

	current = data->env;
	while (current)
	{
		if (ft_strncmp(current->value, "PATH=", 5) == 0)
			return (current->value + 5);
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

	path_var = get_path_from_env(data);
	start = path_var;
	while (start && *start)
	{
		end = ft_strchr(start, ':');
		if (end)
			*end = '\0';
		strcpy(full_path, start);
		strcat(full_path, "/");
		strcat(full_path, cmd);
		if (access(full_path, X_OK) == 0)
		{
			if (end)
				*end = ':';
			return (strdup(full_path));
		}
		if (end)
			start = end + 1;
		else
			break ;
	}
	return (NULL);
}
