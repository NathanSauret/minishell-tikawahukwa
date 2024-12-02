/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:37:27 by jmiccio           #+#    #+#             */
/*   Updated: 2024/12/02 14:38:16 by jmiccio          ###   ########.fr       */
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
