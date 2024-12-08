/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:37:27 by jmiccio           #+#    #+#             */
/*   Updated: 2024/12/08 22:06:32 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_newline(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] != '-')
		return (1);
	i++;
	if (arg[i] == 'n')
	{
		while (arg[i])
		{
			if (arg[i] != 'n')
				return (1);
			i++;
		}
		return (0);
	}
	return (1);
}

int	ft_echo(char **arg)
{
	int	new_line;
	int	i;

	i = 1;
	if (!arg[i])
	{
		ft_printf("\n");
		return (0);
	}
	new_line = is_newline(arg[i]);
	while (!is_newline(arg[i]))
		i++;
	while (arg[i])
	{
		ft_printf("%s", arg[i]);
		i++;
		if (arg[i])
			ft_printf(" ");
	}
	if (new_line)
		ft_printf("\n");
	return (0);
}
