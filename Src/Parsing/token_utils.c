/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:47:28 by j_sk8             #+#    #+#             */
/*   Updated: 2024/12/06 14:32:12 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_cmd(t_token *token)
{
	t_token	*tmp;
	t_token	*head;

	if (!token)
		return (1);
	tmp = ft_token_lstlast(token);
	head = tmp;
	if (tmp->type == PIPE)
		return (1);
	if (head->type == PIPE)
		head = head->prev;
	while (head->prev && head->prev->type != PIPE)
		head = head->prev;
	if (is_operator2(tmp->type, 0))
		return (0);
	if (is_operator2(head->type, 0)
		&& (head->next && head->next->type == ARG && !head->next->next))
		return (1);
	else
		return (0);
	return (0);
}

int	is_operator2(int type, int pipe)
{
	if (type == 1 || type == 2 || type == 3 || type == 4)
		return (1);
	if (pipe)
	{
		if (type == 5)
			return (1);
	}
	return (0);
}

int	token_parsing(t_data *data)
{
	t_token	*current;

	current = data->token;
	if (line_is_empty(current->str))
		return (is_error(NULL, data, 0));
	while (current)
	{
		if ((current->type == PIPE && !current->prev)
			|| (current->type == PIPE && !current->next)
			|| (is_operator2(current->type, 0)
				&& (current->next && current->next->type == PIPE)))
			return (is_error
				("error near unexpected token '|'\n", data, 2));
		else if (is_operator2(current->type, 0) && (!current->next))
			return (is_error
				("error near unexpected token 'new line'\n", data, 2));
		else if (is_operator2(current->type, 0)
			&& (current->next && is_operator2(current->next->type, 0)))
			return (is_error
				("error near unexpected token 'redirect'\n", data, 2));
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
