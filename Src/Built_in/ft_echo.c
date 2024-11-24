/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:37:27 by jmiccio           #+#    #+#             */
/*   Updated: 2024/11/24 18:12:38 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_echo(char **arg)
{
	int	new_line;
	int	i;

	i = 1;
	new_line = 1;
	if (!arg[i])
	{
		ft_printf("\n");
		return (1);
	}
	if (ft_strnstr(arg[i], "-n", 2))
	{
		new_line = 0;
		i++;
	}
	while (arg[i])
	{
		ft_printf("%s ", arg[i]);
		i++;
	}
	if (new_line)
		ft_printf("\n");
	return (1);
}
