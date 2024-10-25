/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:40:34 by j_sk8             #+#    #+#             */
/*   Updated: 2024/10/25 16:05:23 by jmiccio          ###   ########.fr       */
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

int	is_builtin(char *str)
{
	if (ft_strnstr((str), "exit", 4))
		return (1);
	/*else if (ft_strnstr((str), "echo", 4))
		return (1);
	else if (ft_strnstr((str), "cd", 2))
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
	if (!(add_token(data)))
		return (is_error(ERR_MALLOC, data));
	print_token(data->token);
	data->args = tokens_to_args(data->token);
	if (!data->args)
		return (is_error(ERR_MALLOC, data));
	if (!(token_parsing(data)))
		return (0);
	if (!(check_valid_cmd(data)))
		return (is_error(NULL, data));
	if (!data->args)
		return (is_error(ERR_MALLOC, data));
	return (1);
}
