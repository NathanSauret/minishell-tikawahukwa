/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:05:28 by j_sk8             #+#    #+#             */
/*   Updated: 2024/11/07 17:53:38 by j_sk8            ###   ########.fr       */
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
		if (str[i] == '$' && str[i + 1] && !ft_is_space(str[i + 1]))
		{
			v_pos[*v_num] = i + 1;
			v_len[*v_num] = 0;
			i++;
			while (str[i] && str[i] != '$' && !ft_is_space(str[i]))
			{
				v_len[*v_num]++;
				i++;
			}
			(*v_num)++;
		}
		else
			i++;
	}
	return (fill_var_name(str, *v_num, v_pos, v_len));
}

int	get_new_str(t_token *token, char **var, int len)
{
	char	*res;
	int		i;
	int		v_num;
	char	*str;

	str = token->str;
	i = 0;
	v_num = 0;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (0);
	while (i < len && *str)
	{
		if (!copy_str(&res, &str, &i, len) || !var[v_num])
			break ;
		while (*++str && *str != '$' && !ft_is_space(*str))
			;
		copy_var(&res, var[v_num++], &i, len);
	}
	res[i] = '\0';
	free(token->str);
	free_var(var, v_num);
	token->str = res;
	return (1);
}

char	**replace_var_env(char **var, int v_num)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = malloc(sizeof(char *) * (v_num + 1));
	if (!tmp)
		return (0);
	while (i < v_num)
	{
		tmp[i] = ft_strdup(getenv(var[i]));
		if (!tmp)
			return (free_var(tmp, i), free_var(var, v_num));
		i++;
	}
	tmp[i] = NULL;
	free_var(var, v_num);
	return (tmp);
}

int	replace_dolar(t_data *data, t_token *token, char *str)
{
	int		len;
	char	**var;
	int		var_num;

	var_num = 0;
	var = get_var_name(str, &var_num);
	if (!var)
		return (is_error(ERR_MALLOC, data));
	len = full_len(token, var);
	var = replace_var_env(var, var_num);
	if (!(get_new_str(token, var, len)))
		return (is_error(ERR_MALLOC, data));
	return (1);
}

int	handle_dolar(t_data *data)
{
	char	*str;
	t_token	*token;

	token = data->token;
	while (token)
	{
		str = ft_strchr(token->str, '$');
		if (str)
		{
			if (!(replace_dolar(data, token, str)))
				return (0);
		}
		str = NULL;
		token = token->next;
	}
	return (1);
}
