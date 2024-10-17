/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 21:38:42 by j_sk8             #+#    #+#             */
/*   Updated: 2024/10/17 13:52:41 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_shell_level()
{
	char *shlvl = getenv("SHLVL");
	if (shlvl)
	{
		return atoi(shlvl);
	}
	return 0;
}


int	main(int argc, char **argv, char **env)
{
	t_data	data;
	int		i;

	(void)argc;
	(void)argv;
	env_init(&data, env);
	free_env(data.env);
	while (1)
	{
		data.input = readline("minishell> ");
		if (data.input == NULL)
			break ;
		add_history(data.input);
		data.token = strtok(data.input, " ");
		i = 0;
		while (data.token != NULL && i < MAX_ARGS - 1)
		{
			data.args[i++] = data.token;
			data.token = strtok(NULL, " ");
		}
		data.args[i] = NULL;
		data.pid = fork();
		if (data.pid < 0)
		{
			perror("fork");
			free(data.input);
			exit(EXIT_FAILURE);
		}
		if (data.pid == 0)
		{
			execvp(data.args[0], data.args);
			perror("execvp");
			exit(EXIT_FAILURE);
		}
		else
			wait(NULL);
		free(data.input);
	}
	return (0);
}
