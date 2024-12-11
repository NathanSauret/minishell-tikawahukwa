/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:37:27 by jmiccio           #+#    #+#             */
/*   Updated: 2024/12/11 11:45:16 by jmiccio          ###   ########.fr       */
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

static void	cpy_echo_str(int i, char **arg, int new_line)
{
	int		cpy;
	int		y;
	char	res[MAX_LENGTH];

	y = 0;
	cpy = 0;
	ft_bzero(res, MAX_LENGTH);
	while (arg[i] && cpy < MAX_LENGTH - 1)
	{
		y = 0;
		while (arg[i][y] && cpy < MAX_LENGTH - 1)
		{
			res[cpy++] = arg[i][y++];
		}
		i++;
		if (arg[i] && cpy < MAX_LENGTH - 1)
		{
			res[cpy] = ' ';
			cpy++;
		}
	}
	if (new_line)
		res[cpy] = '\n';
	write(1, &res, ft_strlen(res));
}

int	ft_echo(char **arg)
{
	int		new_line;
	int		i;

	i = 1;
	if (!arg[i])
	{
		printf("\n");
		return (0);
	}
	new_line = is_newline(arg[i]);
	if (!new_line)
	{
		while (!is_newline(arg[i]))
			i++;
	}
	cpy_echo_str(i, arg, new_line);
	return (0);
}
