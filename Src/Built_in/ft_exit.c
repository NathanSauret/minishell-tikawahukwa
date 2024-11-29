/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:39:22 by j_sk8             #+#    #+#             */
/*   Updated: 2024/11/29 15:00:01 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_is_exit_arg_a_number(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i])
			&& arg[i] != '"'
			&& arg[i] != '-'
			&& arg[i] != '+')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_exit(t_data *data, char **cmd)
{
	ft_printf("exit\n");
	if (cmd[1])
	{
		if (cmd[2])
		{
			terminate(data, "too many arguments\n", 1);
		}
		else if (!ft_is_exit_arg_a_number(cmd[1]))
		{
			terminate(data, "numeric argument required\n", 2);
		}
		else
		{
			terminate(data, NULL, ft_atoi(cmd[1]));
		}
	}
	else
	{
		terminate(data, NULL, 0);
	}
}
