/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:47:54 by j_sk8             #+#    #+#             */
/*   Updated: 2024/12/11 10:52:33 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	add_cmd(t_data *data, char *str, int len, int type)
{
	char	*token;
	char	quote;

	quote = '$';
	token = ft_substr(str, is_quote(*str), len);
	if (!token)
		return (0);
	if (*str != '\'' && ft_strnstr(str, "$", len))
	{
		if (is_quote(*str))
			quote = *str;
		token = handle_dolar(data, token, &len, quote);
		if (!token)
			return (0);
	}
	if (line_is_empty(token) && !is_quote(*str))
		return (1);
	if (!(ft_token_lstadd_back(&(data->token), ft_token_lstnew(token, type))))
		return (0);
	return (1);
}

static int	join_token(t_data *data, t_token *token, char *str, int len)
{
	char	quote;
	char	*res;

	quote = '$';
	res = ft_substr(str, is_quote(*str), len);
	if (!res)
		return (0);
	if (*str != '\'' && ft_strnstr(str, "$", len))
	{
		if (is_quote(*str))
			quote = *str;
		res = handle_dolar(data, res, &len, quote);
		if (!res)
			return (0);
	}
	token->str = ft_strjoin(token->str, res);
	if (!token->str)
		return (0);
	return (1);
}

int	get_arg(t_data *data, char **str)
{
	int			len;
	int			type;
	int			space;
	t_token		*tmp;

	tmp = ft_token_lstlast(data->token);
	len = token_len(*str, &space, tmp);
	len = get_type(data->token, *str, &type, len);
	if (!len && !is_quote(*(*str)))
		return ((*str) += (1 + is_quote(*(*str))), 1);
	if (tmp && (!space && !is_operator2(tmp->type, 1)))
	{
		if (!(join_token(data, tmp, *(str), len)))
			return (0);
	}
	else
	{
		if (!(add_cmd(data, *str, len, type)))
			return (0);
	}
	if (is_quote(*(*str)))
		return ((*str) += len + 2, 1);
	return ((*str) += len, 1);
}

int	add_token(t_data *data)
{
	char	*cmd;

	cmd = data->input;
	while (*cmd)
	{
		while (*cmd && (ft_is_space(*cmd)))
			cmd++;
		if (*cmd && !(get_arg(data, &cmd)))
			return (0);
		if (data->token && ft_token_lstlast(data->token)->type == PIPE)
			data->num_of_pipe += 1;
	}
	return (1);
}
