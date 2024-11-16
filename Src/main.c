/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 21:38:42 by j_sk8             #+#    #+#             */
/*   Updated: 2024/11/16 17:13:41 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		data_init(&data);
		env_init(&data, env);
		exec_test(argv[1], &data, env);
		free_env(data.env);
	}
	else
	{
		(void)argc;
		(void)argv;
		data_init(&data);
		env_init(&data, env);
		loop(&data, env);
		free_env(data.env);
		clear_history();
	}
	return (0);
}
