/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:36:26 by jmiccio           #+#    #+#             */
/*   Updated: 2024/12/05 20:07:57 by jmiccio          ###   ########.fr       */
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
	if (g_signal_pid == PROMPT)
	{
		clear_rl_line();
		rl_redisplay();
	}
}

void	here_doc_handler(int sig)
{
	if (g_signal_pid == PROMPT)
	{
		(void)sig;
		g_signal_pid = 130;
		close(STDIN_FILENO);
		printf("\n");
		rl_replace_line("", 0);
	}
}

void	signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
