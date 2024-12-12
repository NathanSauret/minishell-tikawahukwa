/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:39:22 by j_sk8             #+#    #+#             */
/*   Updated: 2024/12/12 18:44:54 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static long long	ft_lluatoi(const char *nptr)
{
	unsigned long long	num;
	int					sign;

	sign = 1;
	num = 0;
	while (ft_is_space(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (ft_isdigit(*nptr))
	{
		num = num * 10 + (*nptr - '0');
		if (sign == 1 && num > 9223372036854775807)
			return (0);
		else if (sign == -1 && num > 9223372036854775808LLU)
			return (0);
		nptr++;
	}
	return (num * sign);
}

static int	ft_is_exit_arg_a_number(char *arg)
{
	int			i;
	long long	numercic_arg;

	numercic_arg = ft_lluatoi(arg);
	if ((numercic_arg == 0 && arg[0] != '0' && ft_strlen(arg) != 1)
		|| (ft_strlen(arg) == 1 && ft_is_space(arg[0])))
		return (2);
	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i])
			&& arg[i] != '"'
			&& arg[i] != '-'
			&& arg[i] != '+'
			&& !ft_is_space(arg[i]))
			return (2);
		else if (arg[i + 1] && ft_is_space(arg[i]) && !ft_is_space(arg[i + 1]))
			return (2);
		i++;
	}
	return (0);
}

void	ft_exit(t_data *data, char **cmd)
{
	int	check_res;

	check_res = data->exit_status;
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
		else
		{
			terminate(data, NULL, ft_atoi(cmd[1]));
		}
	}
	else
	{
		terminate(data, NULL, check_res);
	}
}
