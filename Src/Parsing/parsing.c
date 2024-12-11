/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:40:34 by j_sk8             #+#    #+#             */
/*   Updated: 2024/12/11 12:16:20 by jmiccio          ###   ########.fr       */
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

int	parsing(t_data *data)
{
	if (g_signal_pid == SIGINT)
	{
		data->exit_status = 130;
		g_signal_pid = 0;
	}
	if (!(check_quote(data, data->input)))
		return (is_error("quote error\n", data, 2));
	if (!(add_token(data)))
		terminate(data, ERR_MALLOC, 1);
	if (!(token_parsing(data)))
		return (0);
	if (!(get_sorted_arg(data)))
		terminate(data, ERR_MALLOC, 1);
	if (!(fill_cmd_struct(data)))
		terminate(data, ERR_MALLOC, 1);
	data->env_array = lst_to_arr(data->env, data->env_len);
	if (!data->env_array)
		terminate(data, ERR_MALLOC, 1);
	return (1);
}
