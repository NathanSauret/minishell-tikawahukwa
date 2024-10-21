/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 23:27:38 by j_sk8             #+#    #+#             */
/*   Updated: 2024/10/21 23:53:48 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
			q = 1;
		}
		else if ((*str == '\'' && q == 1) || (*str == '"' && dq == 1))
			return (1);
		str++;
	}
	if (q == 0 && dq == 0)
		return (1);
	return (0);
}

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

int	is_quote(char c)
{
	return ((c == '\'' || c == '"'));
}
