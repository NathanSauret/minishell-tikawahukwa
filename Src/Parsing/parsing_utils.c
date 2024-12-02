/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 23:27:38 by j_sk8             #+#    #+#             */
/*   Updated: 2024/12/02 16:20:55 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*escape_sequance_handler(char *str, int len)
{
	char	*res;
	int		i;
	int		j;

	j = 0;
	i = 0;
	res = malloc(sizeof(char) * len + 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\\')
			i++;
		res[j] = str[i];
		i++;
		j++;
	}
	res[j] = '\0';
	return (res);
}

char	*convert_str(t_data *data, char *str, int len)
{
	int		i;
	char	*res;
	int		res_len;

	res_len = len;
	i = 0;
	while (str[i] && i < len)
	{
		if (str[i] == '\\')
		{
			res_len--;
			if (str[i + 1] && str[i + 1] == '\\')
				i++;
		}
		i++;
	}
	res = escape_sequance_handler(str, res_len);
	if (!res)
		terminate(data, ERR_MALLOC, 1);
	return (res);
}

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
