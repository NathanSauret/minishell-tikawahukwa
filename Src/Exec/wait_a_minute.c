/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_a_minute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:16:56 by nsauret           #+#    #+#             */
/*   Updated: 2024/12/09 16:57:31 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	wait_a_minute(t_data *data)
{
	int		pid;
	char	*sleep_cmd[3];

	pid = fork();
	if (pid == -1)
		terminate(data, ERR_FORK, 1);
	if (pid == 0)
	{
		sleep_cmd[0] = "sleep";
		sleep_cmd[1] = "0.001";
		sleep_cmd[2] = NULL;
		execve("/usr/bin/sleep", sleep_cmd, data->env_array);
		terminate(data, "hello wolrd", 0);
	}
	waitpid(pid, NULL, 0);
}
