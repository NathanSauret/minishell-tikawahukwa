/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:40:34 by j_sk8             #+#    #+#             */
/*   Updated: 2024/11/07 17:54:19 by j_sk8            ###   ########.fr       */
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

int	get_sorted_arg(t_data *data)
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

int	is_builtin(char *str)
{
	if (ft_strnstr((str), "exit", 4))
		return (1);
	else if (ft_strnstr((str), "cd", 2))
		return (1);
	/*else if (ft_strnstr((str), "echo", 4))
		return (1);
	if (ft_strnstr((str), "env", 3))
		return (1);
	else if (ft_strnstr((str), "export", 6))
		return (1);
	else if (ft_strnstr((str), "unset", 4))
		return (1);
	else if (ft_strnstr((str), "pwd", 3))
		return (1);*/
	return (0);
}

int	check_valid_cmd(t_data *data)
{
	t_token	*tmp;
	char	*path;

	path = NULL;
	tmp = data->token;
	while (tmp)
	{
		if (tmp->type == CMD)
		{
			if (is_builtin(tmp->str))
				tmp->is_builtin = 1;
			else
			{
				path = get_ex_path(tmp->str, data);
				if (!path)
					return (printf("%s: command not found\n", tmp->str), 0);
				tmp->path = path;
			}
		}
		tmp = tmp->next;
	}
	return (1);
}

int	parsing(t_data *data)
{
	if (!(check_quote(data->input)))
		return (is_error("quote error\n", data));
	if (!(add_token(data)) || !(handle_dolar(data)))
		return (is_error(ERR_MALLOC, data));
	data->args = tokens_to_args(data->token);
	if (!data->args)
		return (is_error(ERR_MALLOC, data));
	if (!(get_sorted_arg(data)))
		return (is_error(ERR_MALLOC, data));
	if (!(token_parsing(data)))
		return (0);
	if (!(check_valid_cmd(data)))
		return (is_error(NULL, data));
	if (!data->args)
		return (is_error(ERR_MALLOC, data));
	if (!(fill_cmd_struct(data)))
		return (is_error(ERR_MALLOC, data));
	print_token(data->token, 0);
	print_cmd(data->cmd);
	return (1);
}
