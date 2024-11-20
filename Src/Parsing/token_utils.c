/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:47:28 by j_sk8             #+#    #+#             */
/*   Updated: 2024/11/20 18:59:59 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_redirect(char *str)
{
	if (ft_strnstr((str), "<<", 2))
		return (1);
	else if (ft_strnstr((str), ">>", 2))
		return (1);
	if (ft_strnstr((str), "<", 1))
		return (1);
	else if (ft_strnstr((str), ">", 1))
		return (1);
	return (0);
}

int	token_parsing(t_data *data)
{
	t_token	*current;

	current = data->token;
	while (current)
	{
		if ((current->type == PIPE && !current->prev)
			|| (current->type == PIPE && !current->next)
			|| (is_redirect(current->str) && current->next->type == PIPE))
			return (is_error("error near unexpected token '|'\n", data));
		else if (is_redirect(current->str) && (!current->next))
			return (is_error("error near unexpected token 'new line'\n", data));
		else if (is_redirect(current->str) && is_redirect(current->next->str))
			return (is_error("error near unexpected token 'redirect'\n", data));
		current = current->next;
	}
	return (1);
}

int	token_len(char *str, int *space, t_token *token)
{
	int		i;
	char	quote;

	i = 0;
	*space = 1;
	if (str[i] && is_quote(str[i]))
	{
		if (token && str[i - 1] && !ft_is_space(str[i - 1]))
			*space = 0;
		quote = str[i++];
		while (str[i] && str[i] != quote)
			i++;
		return (i - 1);
	}
	if (token && str[i - 1] && !is_operator(&str[i])
		&& !ft_is_space(str[i - 1]))
		*space = 0;
	while (str[i] && !ft_is_space(str[i]) && !is_quote(str[i])
		&& !is_operator(&str[i]))
		i++;
	if (is_operator(&str[i]) && i == 0)
		i++;
	return (i);
}

int	is_cmd(t_token *token)
{
	t_token	*tmp;

	if (!token)
		return (1);
	tmp = ft_token_lstlast(token);
	if (tmp->type == PIPE || (tmp->prev && is_redirect(tmp->prev->str)))
		return (1);
	return (0);
}

int	get_type(t_token *token, char *str, int *type, int len)
{
	if (ft_strnstr((str), "<<", 2))
		return (*type = HEREDOC, 2);
	else if (ft_strnstr((str), "<", 1))
		return (*type = INPUT, 1);
	else if (ft_strnstr((str), ">>", 2))
		return (*type = APPEND, 2);
	else if (ft_strnstr((str), ">", 1))
		return (*type = TRUNC, 1);
	else if (ft_strnstr((str), "|", 1))
		return (*type = PIPE, 1);
	else if (is_cmd(token))
		return (*type = CMD, len);
	return (*type = ARG, len);
}
