/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:39:40 by j_sk8             #+#    #+#             */
/*   Updated: 2024/12/13 11:10:24 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	copy_str(char **res, char **str, int *i, int len)
{
	static int	is_on_quote = 0;

	while (**str && *i < len)
	{
		is_on_quote = get_quote_state(**str, is_on_quote);
		if (is_on_quote != 2 && **str == '$' && (*str)[1]
			&& (ft_isalnum((*str)[1]) || (*str)[1] == '_'
				|| (*str)[1] == '?'))
			break ;
		(*res)[(*i)++] = *((*str)++);
	}
	return (**str == '$');
}

int	copy_var(char **res, char *var, int *i, int len)
{
	int	y;

	y = 0;
	while (var[y] && *i < len)
		(*res)[(*i)++] = var[y++];
	return (y);
}

int	var_len(char *str, int *y)
{
	int	i;

	i = 0;
	if (ft_isdigit(*str) || *str == '?')
		return (*y += 1, 1);
	while (str[i] && (ft_isalnum(str[i])
			|| str[i] == '_') && !is_quote(str[i]))
		i++;
	*y += i;
	return (i);
}

char	**fill_var_name(char *str, int v_num, int v_pos[100], int v_len[100])
{
	char	**res;
	int		i;

	i = 0;
	if (!v_num)
		return (NULL);
	res = malloc(sizeof(char *) * (v_num + 1));
	if (!res)
		return (NULL);
	while (i < v_num)
	{
		res[i] = ft_substr(&str[v_pos[i]], 0, v_len[i]);
		if (!res[i])
			return (free_var(res, i));
		i++;
	}
	res[v_num] = NULL;
	return (res);
}

int	full_len(t_data *data, char *token, char **var)
{
	int	full_v_len;
	int	total_len;
	int	i;

	i = 0;
	full_v_len = 0;
	while (var[i])
	{
		full_v_len += ft_strlen(var[i]) + 1;
		i++;
	}
	total_len = ft_strlen(token) - full_v_len;
	full_v_len = 0;
	i = 0;
	while (var[i])
	{
		if (var[i][0] == '?')
			full_v_len += ft_intlen(data->exit_status);
		else
			full_v_len += ft_strlen(ft_getenv(data->env, var[i]));
		i++;
	}
	total_len += full_v_len;
	return (total_len);
}
