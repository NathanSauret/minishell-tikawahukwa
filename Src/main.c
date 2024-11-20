/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 21:38:42 by j_sk8             #+#    #+#             */
/*   Updated: 2024/11/20 15:17:45 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_rl_line(void)
{
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	handle_sigint(int sig)
{
	(void)sig;
	printf("\n");
	clear_rl_line();
	rl_redisplay();
}

int	loop(t_data *data, char **env)
{
	while (1)
	{
		data->input = readline("minishell> ");
		if (data->input == NULL)
			return (printf("exit..\n"), 1);
		add_history(data->input);
		if (line_is_empty(data->input))
		{
			free(data->input);
			continue ;
		}
		if (!parsing(data))
			continue ;
		if ((exec(data, env)) == -1)
			break ;
		free_token(data);
	}
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	if (argc > 1)
	{
		signal(SIGINT, handle_sigint);
		data_init(&data);
		env_init(&data, env);
		exec_test(argv[1], &data, env);
		free_env(data.env);
	}
	else
	{
		(void)argc;
		(void)argv;
		signal(SIGINT, handle_sigint);
		data_init(&data);
		env_init(&data, env);
		loop(&data, env);
		free_env(data.env);
		clear_history();
	}
	return (0);
}
