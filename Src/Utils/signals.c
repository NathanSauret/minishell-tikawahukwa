/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:36:26 by jmiccio           #+#    #+#             */
/*   Updated: 2024/12/03 23:43:49 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	clear_rl_line(void)
{
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	handle_sigint(int sig)
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

void	here_doc_handler(int sig)
{
	(void)sig;
	g_signal_pid = 1;
	rl_done = 1;
	printf("\n");
	clear_rl_line();
	rl_redisplay();
}

void	signals(void)
{
	rl_done = 0;
	g_signal_pid = 0;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
