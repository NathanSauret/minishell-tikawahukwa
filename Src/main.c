/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 21:38:42 by j_sk8             #+#    #+#             */
/*   Updated: 2024/10/18 23:04:31 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argc;
	(void)argv;
	data_init(&data);
	env_init(&data, env);
	while (1)
	{
		data.input = readline("minishell> ");
		if (data.input == NULL)
			return (exit_error2(&data, "exit\n"));
		add_history(data.input);
		if (line_is_empty(data.input))
		{
			free(data.input);
			continue ;
		}
		if (!parsing(&data))
			continue ;
		exec(&data, env);
		free_token(&data);
	}
	free_env(data.env);
	return (0);
}
