/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 17:10:52 by jmiccio           #+#    #+#             */
/*   Updated: 2024/12/11 11:04:00 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

pid_t	g_signal_pid;

void	prompt(t_data *data)
{
	if (data->is_nl)
		write(1, "\n", 1);
	data->is_nl = 0;
	g_signal_pid = 0;
	data->input = readline(BOLD_GREEN"~ Tikawahukwa ☕ "BLUE"> "RESET);
}

static void	loop(t_data *data)
{
	while (1)
	{
		prompt(data);
		if (data->input == NULL)
			return ;
		add_history(data->input);
		if (line_is_empty(data->input))
		{
			free(data->input);
			continue ;
		}
		if (!parsing(data))
			continue ;
		if ((exec(data)) == -1)
			break ;
		free_token(data);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argv;
	(void)argc;
	data_init(&data);
	data.env_len = env_init(&data, env);
	if (!data.env_len)
		terminate(&data, "env_error\n", data.exit_status);
	loop(&data);
	printf("exit\n");
	terminate(&data, NULL, 0);
}
