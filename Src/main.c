/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 17:10:52 by jmiccio           #+#    #+#             */
/*   Updated: 2024/12/06 15:57:50 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

pid_t	g_signal_pid;

void	prompt(t_data *data)
{
	if (data->is_space >= 128)
		write(1, "\n", 1);
	data->is_space = 0;
	g_signal_pid = 0;
	data->input = readline(BOLD_GREEN"~ Tikawahukwa ☕ "BLUE"> "RESET);
}

static void	loop(t_data *data)
{
	while (1)
	{
		prompt(data);
		if (data->input == NULL)
			terminate(data, NULL, 0);
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
	int		i;

	i = 2;
	data_init(&data);
	data.env_len = env_init(&data, env);
	if (!data.env_len)
		terminate(&data, "env_error\n", data.exit_status);
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
	terminate(&data, NULL, 0);
}
