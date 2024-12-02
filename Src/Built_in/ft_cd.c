/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:37:43 by j_sk8             #+#    #+#             */
/*   Updated: 2024/12/02 23:14:43 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_cd(t_env *env, char **args)
{
	char	*home;

	home = ft_getenv(env, "HOME");
	if (args[1] == NULL)
	{
		if (home == NULL || chdir(home) != 0)
		{
			perror("cd");
			return (1);
		}
	}
	else
	{
		if (args[2])
		{
			ft_printerr("Minishell: cd :too many arguments\n");
			return (1);
		}
		if (chdir(args[1]) != 0)
		{
			perror("Minishell: cd");
			return (1);
		}
	}
	return (0);
}
