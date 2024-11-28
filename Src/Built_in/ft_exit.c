/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:39:22 by j_sk8             #+#    #+#             */
/*   Updated: 2024/11/28 15:59:07 by nsauret          ###   ########.fr       */
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

void	ft_exit(t_data *data)
{
	ft_printf("exit\n");
	if (data->token->next)
	{
		if (data->token->next->next)
		{
			terminate(data, "too many arguments\n", 1);
		}
		else if (!ft_is_exit_arg_a_number(data->token->next->str))
		{
			terminate(data, "numeric argument required\n", 2);
		}
		else
		{
			terminate(data, NULL, ft_atoi(data->token->next->str));
		}
	}
	else
	{
		terminate(data, NULL, 0);
	}
}
