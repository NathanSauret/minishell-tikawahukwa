/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:36:26 by jmiccio           #+#    #+#             */
/*   Updated: 2024/12/12 16:35:20 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_sigint(int sig)
{
	g_signal = sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	here_doc_handler(int sig)
{
	g_signal = sig;
	rl_replace_line("", 0);
	rl_clear_message();
	close(STDIN_FILENO);
}

static void	handle_sigsegv(int code)
{
	(void)code;
	write(2, "Segmentation fault\n", 19);
	exit(11);
}

static void	handle_sigabrt(int code)
{
	(void)code;
	write(1, "abort\n", 6);
	exit(134);
}

void	signals(void)
{
	signal(SIGABRT, &handle_sigabrt);
	signal(SIGSEGV, &handle_sigsegv);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
