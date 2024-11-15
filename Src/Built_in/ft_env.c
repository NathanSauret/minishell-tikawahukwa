/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:19:11 by jmiccio           #+#    #+#             */
/*   Updated: 2024/11/15 18:27:23 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_env(t_env *env)
{
	if (!env)
		return (0);
	if (ft_strchr(env->value, '='))
		ft_printf("%s\n", env->value);
	env = env->next;
	while (env != NULL)
	{
		if (ft_strchr(env->value, '='))
			ft_printf("%s\n", env->value);
		env = env->next;
	}
	return (0);
}
