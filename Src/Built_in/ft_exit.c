/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:39:22 by j_sk8             #+#    #+#             */
/*   Updated: 2024/12/08 15:16:25 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_is_exit_arg_a_number(char *arg)
{
	int	i;

	if (arg[0] == '-' && ft_strncmp(arg, "-9223372036854775808", 21) > 0)
		return (255);
	else if (ft_strncmp(arg, "9223372036854775807", 20) > 0)
		return (255);
	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i])
			&& arg[i] != '"'
			&& arg[i] != '-'
			&& arg[i] != '+')
		{
			return (2);
		}
		i++;
	}
	return (0);
}

void	ft_exit(t_data *data, char **cmd)
{
	int	check_res;

	ft_printf("exit\n");
	if (cmd[1])
	{
		if (cmd[2])
		{
			terminate(data, " too many arguments\n", 1);
		}
		check_res = ft_is_exit_arg_a_number(cmd[1]);
		if (check_res == 2)
			terminate(data, " numeric argument required\n", 2);
		if (check_res == 255)
			terminate(data, " numeric argument required\n", 2);
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
