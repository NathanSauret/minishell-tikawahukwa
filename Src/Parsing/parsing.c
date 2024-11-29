/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:40:34 by j_sk8             #+#    #+#             */
/*   Updated: 2024/11/28 19:53:09 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	fill_command_line(t_token *head, int size)
{
	int		i;
	t_token	*tmp;

	tmp = head;
	head->command_line = malloc(sizeof(char *) * (size + 1));
	if (!head->command_line)
		return (0);
	i = 0;
	head->cmd_line_size = size;
	while (tmp && tmp->type != PIPE)
	{
		head->command_line[i++] = tmp->str;
		tmp = tmp->next;
	}
	head->command_line[i] = NULL;
	return (1);
}

static int	get_sorted_arg(t_data *data)
{
	t_token	*tmp;
	t_token	*head;
	int		i;
	int		pipe;

	tmp = data->token;
	pipe = 0;
	while (pipe < data->num_of_pipe + 1)
	{
		i = 0;
		head = tmp;
		while (tmp && tmp->type != PIPE)
		{
			i++;
			tmp = tmp->next;
		}
		fill_command_line(head, i);
		if (tmp && tmp->type == PIPE)
			tmp = tmp->next;
		pipe++;
	}
	return (1);
}

static int	is_builtin(char *str)
{
	if (!(ft_strncmp("exit", str, MAX_PATH_LENGTH)))
		return (1);
	else if (!(ft_strncmp("cd", str, MAX_PATH_LENGTH)))
		return (1);
	else if (!(ft_strncmp("echo", str, MAX_PATH_LENGTH)))
		return (1);
	else if (!(ft_strncmp("env", str, MAX_PATH_LENGTH)))
		return (1);
	else if (!(ft_strncmp("export", str, MAX_PATH_LENGTH)))
		return (1);
	else if (!(ft_strncmp("unset", str, MAX_PATH_LENGTH)))
		return (1);
	else if (!(ft_strncmp("pwd", str, MAX_PATH_LENGTH)))
		return (1);
	return (0);
}

static int	check_valid_cmd(t_data *data)
{
	t_token	*tmp;
	char	*path;

	tmp = data->token;
	while (tmp)
	{
		if (tmp->type == CMD)
		{
			path = NULL;
			if ((ft_strchr(tmp->str, '/'))
				&& (!absolute_path(&path, tmp->str, data)))
				return (is_error(NULL, data, data->exit_status));
			else if (is_builtin(tmp->str))
				tmp->is_builtin = 1;
			else if (tmp->is_builtin == 0 && !(ft_strchr(tmp->str, '/')))
			{
				path = get_ex_path(tmp->str, data);
				if (!path)
					return (is_error("command not found\n", data, 127));
			}
			tmp->path = path;
		}
		tmp = tmp->next;
	}
	return (1);
}

int	parsing(t_data *data)
{
	if (!(check_quote(data, data->input)))
		return (is_error("quote error\n", data, 2));
	if (!(add_token(data)))
		terminate(data, ERR_MALLOC, 1);
	print_token(data->token, 0);
	if (!(token_parsing(data)))
		return (0);
	if (!(check_valid_cmd(data)))
		return (0);
	if (!(get_sorted_arg(data)))
		terminate(data, ERR_MALLOC, 1);
	if (!(fill_cmd_struct(data)))
		terminate(data, ERR_MALLOC, 1);
	data->env_array = lst_to_arr(data->env, data->env_len);
	if (!data->env_array)
		terminate(data, ERR_MALLOC, 1);
	//print_token(data->token, 0);
	//print_cmd(data->cmd);
	return (1);
}
