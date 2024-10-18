/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:40:34 by j_sk8             #+#    #+#             */
/*   Updated: 2024/10/18 23:09:11 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
		if (tmp == token_list)
			break ;
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
			dq = 1;
		}
		if ((*str == '\'' && q == 1) || (*str == '"' && dq == 1))
			return (1);
		str++;
	}
	if (q == 0 && dq == 0)
		return (1);
	return (0);
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
		while (*cmd && !ft_is_space(*cmd))
			cmd++;
	}
	return (1);
}

int	parsing(t_data *data)
{
	if (!(check_quote(data->input)))
	{
		printf("quote error\n");
		free_token(data);
		return (0);
	}
	if (!(add_token(data)))
	{
		printf(ERR_MALLOC);
		free_token(data);
		return (0);
	}
	data->arg = tokens_to_args(data->token);
	print_token(data->token);
	if (!data->arg)
	{
		printf(ERR_MALLOC);
		ft_token_lstclear(&(data->token));
		return (0);
	}
	return (1);
}
