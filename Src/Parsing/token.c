/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:47:54 by j_sk8             #+#    #+#             */
/*   Updated: 2024/10/22 00:05:24 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	token_len(char *str, int *len, int *start, int *type)
{
	int		i;
	char	quote;

	i = 0;
	if (is_quote(str[i]))
	{
		*type = ARG;
		*start = 1;
		quote = str[i];
		i++;
		while (str[i] && str[i] != quote)
			i++;
		*len = i - 1;
	}
	else
	{
		*type = 0;
		*start = 0;
		while (str[i] && !(ft_is_space(str[i])))
			i++;
		*len = i;
	}
}

int	add_cmd(t_data *data, char *str, int type)
{
	if (!str)
		return (printf(ERR_MALLOC), 0);
	if (!(ft_token_lstadd_back(&(data->token), ft_token_lstnew(str, type))))
		return (printf(ERR_MALLOC), 0);
	return (1);
}

int	get_type(char *str, int *type, int len)
{
	if (ft_strnstr((str), "echo", 4)
		|| ft_strnstr((str), "grep", 4))
		return (*type = CMD, 4);
	if (ft_strnstr((str), "cat", 3))
		return (*type = CMD, 3);
	if (ft_strnstr((str), "ls", 2) || ft_strstr((str), "cd", 2))
		return (*type = CMD, 2);
	else if (ft_strnstr((str), "<<", 2))
		return (*type = HEREDOC, 2);
	else if (ft_strnstr((str), "<", 1))
		return (*type = INPUT, 1);
	else if (ft_strnstr((str), ">>", 2))
		return (*type = APPEND, 2);
	else if (ft_strnstr((str), ">", 1))
		return (*type = TRUNC, 1);
	else if (ft_strnstr((str), "|", 1))
		return (*type = PIPE, 1);
	return (*type = ARG, len);
}

int	get_arg(t_data *data, char **str)
{
	int	len;
	int	start;
	int	type;

	token_len(*str, &len, &start, &type);
	if (!len)
		return ((*str) += 2, 1);
	if (type != ARG)
		len = get_type(*str, &type, len);
	if (!(add_cmd(data, ft_substr(*str, start, len), type)))
		return (0);
	if (is_quote(*(*str)))
		(*str) += len + 1;
	else
		(*str) += len;
	return (1);
}
