/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 17:10:52 by jmiccio           #+#    #+#             */
/*   Updated: 2024/12/17 10:31:03 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal;

void	prompt(t_data *data)
{
	if (data->is_nl)
		write(1, "\n", 1);
	data->is_nl = 0;
	g_signal = 0;
	data->pid = 0;
	data->input = readline(BOLD_GREEN"~ Tikawahukwa ☕ "BLUE"> "RESET);
}

static void	loop(t_data *data)
{
	while (1)
	{
		prompt(data);
		if (data->input == NULL)
			return ;
		if (line_is_empty(data->input))
		{
			free(data->input);
			continue ;
		}
		add_history(data->input);
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
	ft_printf("exit\n");
	terminate(&data, NULL, 0);
}
