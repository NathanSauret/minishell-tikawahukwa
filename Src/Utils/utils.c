/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:07:31 by jmiccio           #+#    #+#             */
/*   Updated: 2024/12/13 11:13:33 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_quote(char c)
{
	return ((c == '\'' || c == '"'));
}

char	*ft_getenv(t_env *env, char *str)
{
	char	*ptr;
	int		size;

	size = ft_strlen(str);
	ptr = NULL;
	while (env)
	{
		if ((!ft_strncmp(env->value, str, size)
				&& (env->value[size] == '=' || env->value[size] == '\0')))
		{
			if ((env->value[size] == '=' && env->value[size + 1] == '\0')
				|| env->value[size] == '\0')
				return ("");
			else
				ptr = &env->value[size + 1];
			return (ptr);
		}
		env = env->next;
	}
	return ("");
}

int	ft_intlen(int n)
{
	int	len;

	len = 1;
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}
