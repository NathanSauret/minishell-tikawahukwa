/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:36:26 by jmiccio           #+#    #+#             */
/*   Updated: 2024/12/01 17:09:45 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	clear_rl_line(void)
{
	rl_replace_line("", 0);
	rl_on_new_line();
}

static void	handle_sigint(int sig)
{
	(void)sig;
	printf("\n");
	if (g_signal_pid > 0)
		kill(g_signal_pid, SIGINT);
	else
	{
		clear_rl_line();
		rl_redisplay();
	}
}

void	signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
