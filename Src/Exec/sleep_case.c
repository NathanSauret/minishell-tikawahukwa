/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_case.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:06:28 by nsauret           #+#    #+#             */
/*   Updated: 2024/11/20 17:43:33 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	get_to_bed(char *max_sleep, char **env)
{
	char	**cmd;

	cmd = ft_calloc(3, sizeof(char *));
	if (!cmd)
		return ;
	cmd[0] = "sleep";
	cmd[1] = max_sleep;
	if (ft_atoi(cmd[1]) > 0)
		execve("/usr/bin/sleep", cmd, env);
	free(cmd);
}

int	sleep_case(char *max_sleep, char **env)
{
	get_to_bed(max_sleep, env);
	return (1);
}
