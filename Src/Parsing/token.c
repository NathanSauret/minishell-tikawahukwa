/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:47:54 by j_sk8             #+#    #+#             */
/*   Updated: 2024/10/18 23:09:32 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_quote(char c)
{
	return ((c == '\'' || c == '"'));
}

void	token_len(char *str, int *len, int *start)
{
	int		i;
	char	quote;

	i = 0;
	if (is_quote(str[i]))
	{
		*start = 1;
		quote = str[i];
		i++;
		while (str[i] && str[i] != quote)
			i++;
		*len = i - 1;
	}
	else
	{
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

int	get_arg(t_data *data, char **str)
{
	int	len;
	int	start;

	token_len(*str, &len, &start);
	if (!(add_cmd(data, ft_substr(*str, start, len), 0)))
		return (0);
	(*str) += len;
	return (1);
}
