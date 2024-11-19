/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:05:28 by j_sk8             #+#    #+#             */
/*   Updated: 2024/11/19 22:30:59 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**get_var_name(char *str, int *v_num)
{
	int		i;
	int		v_len[100];
	int		v_pos[100];

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1]
			&& (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
		{
			v_pos[*v_num] = i + 1;
			i++;
			v_len[*v_num] = var_len(&str[i], &i);
			(*v_num)++;
		}
		else
			i++;
	}
	return (fill_var_name(str, *v_num, v_pos, v_len));
}

char	*get_new_str(char *token, char **var, int len)
{
	char	*res;
	int		i;
	int		v_num;

	i = 0;
	v_num = 0;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	while (i < len && *token)
	{
		if (!copy_str(&res, &token, &i, len) || !var[v_num])
			break ;
		while (*++token && *token != '$'
			&& (ft_isalnum(*token) || *token == '_'))
			;
		copy_var(&res, var[v_num++], &i, len);
	}
	res[i] = '\0';
	free_var(var, v_num + 1);
	return (res);
}

char	**replace_var_env(t_env *env, char **var, int v_num)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = malloc(sizeof(char *) * (v_num + 1));
	if (!tmp)
		return (0);
	while (i < v_num)
	{
		tmp[i] = ft_strdup(ft_getenv(env, var[i]));
		if (!tmp)
			return (free_var(tmp, i), free_var(var, v_num));
		i++;
	}
	tmp[i] = NULL;
	free_var(var, v_num);
	return (tmp);
}

char	*replace_dolar(t_data *data, char *str, int *len, int quote)
{
	char	**var;
	int		var_num;
	char	*res;

	var_num = 0;
	var = get_var_name(str, &var_num);
	if (!var)
		return (is_error(ERR_MALLOC, data), NULL);
	*len = full_len(data->env, str, var);
	var = replace_var_env(data->env, var, var_num);
	res = get_new_str(str, var, *len);
	if (!res)
		return (is_error(ERR_MALLOC, data), NULL);
	if (is_quote(quote))
		*len -= 1;
	return (res);
}

char	*handle_dolar(t_data *data, char *str, int *len, char quote)
{
	char	*token;

	token = replace_dolar(data, str, len, quote);
	free(str);
	if (!token)
		return (NULL);
	return (token);
}
