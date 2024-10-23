/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:40:34 by j_sk8             #+#    #+#             */
/*   Updated: 2024/10/23 15:48:11 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**tokens_to_args(t_token *token_list)
{
	int		count;
	char	**args;
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = token_list;
	count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	args = malloc((count + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	tmp = token_list;
	while (i < count)
	{
		args[i] = tmp->str;
		tmp = tmp->next;
		i++;
	}
	args[count] = NULL;
	return (args);
}

int	token_parsing(t_data *data)
{
	t_token	*current;

	current = data->token;
	while (current)
	{
		if ((current->type == PIPE && !current->prev)
			|| (current->type == PIPE && !current->next))
			return (is_error("error near unexpected token '|'\n", data));
		current = current->next;
	}
	return (1);
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
			path = get_ex_path(tmp->str, data);
			if (!path)
				return (printf("%s: command not found\n", tmp->str), 0);
			tmp->path = path;
		}
		tmp = tmp->next;
	}
	return (1);
}

int	parsing(t_data *data)
{
	if (!(check_quote(data->input)))
		return (is_error("quote error\n", data));
	if (!(add_token(data)))
		return (is_error(ERR_MALLOC, data));
	data->args = tokens_to_args(data->token);
	if (!data->args)
		return (is_error(ERR_MALLOC, data));
	print_token(data->token);
	if (!(token_parsing(data)))
		return (0);
	if (!(check_valid_cmd(data)))
		return (is_error("", data));
	if (!data->args)
		return (is_error(ERR_MALLOC, data));
	return (1);
}
