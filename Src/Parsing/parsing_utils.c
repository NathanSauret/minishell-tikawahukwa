/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 23:27:38 by j_sk8             #+#    #+#             */
/*   Updated: 2024/12/08 23:14:44 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_quote(t_data *data, char *str)
{
	int	q;
	int	dq;

	q = -1;
	dq = -1;
	while (*str)
	{
		if (*str == '"' && (q != 1))
			dq = -dq;
		else if (*str == '\'' && (dq != 1))
			q = -q;
		str++;
	}
	if (q == -1 && dq == -1)
		return (1);
	data->exit_status = 2;
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
