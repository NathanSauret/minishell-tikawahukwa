/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:25:51 by nsauret           #+#    #+#             */
/*   Updated: 2024/12/06 15:54:30 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// case_-1 = problem without msg
// case_0 = with message
// case_1 = with perror
// case_2 = command not found

// static void	permission_denied(int error_case, char **args)

int	exit_error_exec(t_pipex *pipex, int error_case, char *arg)
{
	(void)pipex;
	if (error_case == 0)
	{
		write(2, arg, ft_strlen(arg));
		write(2, "\n", 1);
	}
	else if (error_case == 1)
		perror(arg);
	else if (error_case == 2)
	{
		write(2, arg, ft_strlen(arg));
		write(2, ": command not found\n", 21);
		free(arg);
	}
	return (0);
}
