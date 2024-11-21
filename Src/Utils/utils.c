/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:07:31 by jmiccio           #+#    #+#             */
/*   Updated: 2024/11/21 16:51:30 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_getenv(t_env *env, char *str)
{
	char	*ptr;
	int		size;

	size = ft_strlen(str);
	ptr = NULL;
	while (env)
	{
		if (!ft_strncmp(env->value, str, size)
			&& (env->value[size] == '=' || env->value[size] == '\0'))
		{
			ptr = &env->value[size + 1];
			return (ptr);
		}
		env = env->next;
	}
	return ("");
}

char	**free_var(char **str, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

int	print_error(char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
	return (1);
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
