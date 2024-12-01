/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid Date        by                   #+#    #+#             */
/*   Updated: 2024/11/30 17:07:04 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

pid_t	g_signal_pid;

static int	loop(t_data *data)
{
	while (1)
	{
		data->input = readline("minishell> ");
		if (data->input == NULL)
			return (printf("exit\n"), 1);
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
		g_signal_pid = 0;
	}
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	if (argc > 1)
	{
		data_init(&data);
		data.env_len = env_init(&data, env);
		if (!data.env_len)
			terminate(&data, ERR_MALLOC, data.exit_status);
		exec_test(argv[1], &data);
		free_env(data.env);
	}
	else
	{
		(void)argc;
		(void)argv;
		data_init(&data);
		data.env_len = env_init(&data, env);
		if (!data.env_len)
			terminate(&data, ERR_MALLOC, data.exit_status);
		loop(&data);
		free_env(data.env);
		rl_clear_history();
	}
	return (0);
}
