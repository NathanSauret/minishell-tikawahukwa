/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:40:34 by j_sk8             #+#    #+#             */
/*   Updated: 2024/10/22 00:08:05 by j_sk8            ###   ########.fr       */
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

int	add_token(t_data *data)
{
	char	*cmd;

	cmd = data->input;
	while (*cmd)
	{
		while (*cmd && ft_is_space(*cmd))
			cmd++;
		if (*cmd && !(get_arg(data, &cmd)))
			return (0);
	}
	return (1);
}

int	check_next(t_token *token)
{
	t_token	*tmp;

	tmp = token->next;
	if (!tmp)
		return (0);
	while (tmp)
	{
		if (tmp->type == PIPE)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	token_parsing(t_data *data)
{
	t_token	*current;

	current = data->token;
	while (current)
	{
		if ((current->type == PIPE && !current->prev)
			|| (current->type == PIPE && !current->prev))
			return (is_error("error near unexpected token '|'\n", data));
		else if (current->type == PIPE && current->next->type != CMD)
			if (!(check_next(current)))
				return (printf("%s ", current->next->str),
					is_error("command invalid\n", data), 0);
		current = current->next;
	}
	return (1);
}

int	parsing(t_data *data)
{
	if (!(check_quote(data->input)))
		return (is_error("quote error\n", data));
	if (!(add_token(data)))
		return (is_error(ERR_MALLOC, data));
	data->arg = tokens_to_args(data->token);
	if (!data->arg)
		return (is_error(ERR_MALLOC, data));
	print_token(data->token);
	if (!(token_parsing(data)))
		return (0);
	if (!data->arg)
		return (is_error(ERR_MALLOC, data));
	return (1);
}
