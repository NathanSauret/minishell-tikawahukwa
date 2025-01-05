/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 23:29:47 by jmiccio           #+#    #+#             */
/*   Updated: 2025/01/05 23:39:18 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*replace_home_by_tilde(char *cwd, t_data *data)
{
	char	*home;
	char	*new_cwd;

	home = ft_getenv(data->env, "HOME");
	if (home && ft_strncmp(cwd, home, ft_strlen(home)) == 0)
	{
		new_cwd = malloc(strlen(cwd) - ft_strlen(home) + 2);
		if (!new_cwd)
		{
			free(cwd);
			terminate(data, ERR_MALLOC, 1);
		}
		new_cwd[0] = '~';
		ft_strlcpy(new_cwd + 1, cwd + ft_strlen(home), MAX_LENGTH);
		free(cwd);
		return (new_cwd);
	}
	return (cwd);
}

static char	*create_prompt_str(char *cwd, t_data *data)
{
	char	*prefix;
	size_t	prompt_len;
	char	*prompt_str;

	prefix = BOLD_GREEN "~ Tikawahukwa ☕ " RESET BOLD_BLUE;
	prompt_len = ft_strlen(prefix) + ft_strlen(cwd) + ft_strlen(RESET) + 3;
	prompt_str = malloc(prompt_len);
	if (!prompt_str)
	{
		free(cwd);
		terminate(data, ERR_MALLOC, 1);
	}
	ft_strlcpy(prompt_str, prefix, prompt_len);
	ft_strlcat(prompt_str, cwd, prompt_len);
	ft_strlcat(prompt_str, RESET, prompt_len);
	ft_strlcat(prompt_str, "> ", prompt_len);
	return (prompt_str);
}

void	prompt(t_data *data)
{
	char	*cwd;
	char	*prompt_str;

	if (data->is_nl)
		write(1, "\n", 1);
	data->is_nl = 0;
	g_signal = 0;
	data->pid = 0;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd");
		data->input = readline(BOLD_GREEN "~ Tikawahukwa ☕ >" RESET);
		return ;
	}
	cwd = replace_home_by_tilde(cwd, data);
	prompt_str = create_prompt_str(cwd, data);
	data->input = readline(prompt_str);
	free(prompt_str);
	free(cwd);
}
