/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 17:10:52 by jmiccio           #+#    #+#             */
/*   Updated: 2024/12/02 16:17:33 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

pid_t	g_signal_pid;

static int	loop(t_data *data)
{
	while (1)
	{
		data->input = readline("minishell: ");
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
	int		i;

	i = 2;
	data_init(&data);
	data.env_len = env_init(&data, env);
	if (!data.env_len)
		terminate(&data, ERR_MALLOC, data.exit_status);
	if (argc > 2 && ft_strncmp(argv[1], "-c", MAX_PATH_LENGTH) == 0)
	{
		while (i < argc)
		{
			exec_test(argv[i], &data);
			i++;
		}
	}
	else
		loop(&data);
	free_env(data.env);
	rl_clear_history();
	return (0);
}
