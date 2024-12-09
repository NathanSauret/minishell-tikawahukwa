/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:36:26 by jmiccio           #+#    #+#             */
/*   Updated: 2024/12/09 15:42:45 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	if (g_signal_pid == 0 || g_signal_pid == SIGINT)
	{
		g_signal_pid = SIGINT;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	here_doc_handler(int sig)
{
	(void)sig;
	if (g_signal_pid == 0)
	{
		g_signal_pid = sig;
		close(STDIN_FILENO);
		rl_replace_line("", 0);
	}
}

void	signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
