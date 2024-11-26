/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:47:54 by j_sk8             #+#    #+#             */
/*   Updated: 2024/11/25 22:39:35 by j_sk8            ###   ########.fr       */
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

int	add_cmd(t_data *data, char *str, int len, int type)
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
	if (!(ft_token_lstadd_back(&(data->token), ft_token_lstnew(token, type))))
		return (0);
	return (1);
}

int	join_token(t_data *data, t_token *token, char *str, int len)
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
	if (!len)
		return ((*str) += 1, 1);
	len = get_type(data->token, *str, &type, len);
	if (tmp && ((ft_strlen(tmp->str) == 0)
			|| (!space && !is_operator(tmp->str))))
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
		if (ft_token_lstlast(data->token)->type == PIPE)
			data->num_of_pipe += 1;
	}
	return (1);
}
