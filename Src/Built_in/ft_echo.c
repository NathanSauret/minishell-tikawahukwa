/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:37:27 by jmiccio           #+#    #+#             */
/*   Updated: 2024/10/30 23:22:18 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_echo(char **arg)
{
	int	new_line;
	int	i;

	i = 1;
	new_line = 1;
	if (ft_strnstr(arg[i], "-n", 2))
	{
		new_line = 0;
		i++;
	}
	while (arg[i])
	{
		printf("%s ", arg[i]);
		i++;
	}
	if (new_line)
		printf("\n");
	return (1);
}
