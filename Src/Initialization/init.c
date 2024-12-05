/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 21:40:17 by j_sk8             #+#    #+#             */
/*   Updated: 2024/12/05 22:50:18 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	data_init(t_data *data)
{
	data->token = NULL;
	data->input = NULL;
	data->env = NULL;
	data->cmd = NULL;
	data->env_array = NULL;
	data->pipex = NULL;
	data->env_len = 0;
	data->num_of_pipe = 0;
	data->exit_status = 0;
	g_signal_pid = 0;
	signals();
}

void	copy_shlvl_env(char *res, const char *str, const char *num)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
		{
			k = 0;
			while (num[k])
				res[j++] = num[k++];
			while (ft_isdigit(str[i]))
				i++;
		}
		else
			res[j++] = str[i++];
	}
	res[j] = '\0';
}

static char	*get_new_shlvl(t_data *data, char *str)
{
	int		lvl;
	char	*res;
	int		size;
	int		i;
	char	*num;

	i = 0;
	size = ft_strlen(str);
	if (strchr(str, '9'))
		size++;
	while (str[i] && !ft_isdigit(str[i]))
		i++;
	lvl = ft_atoi(&str[i]);
	lvl++;
	num = ft_itoa(lvl);
	if (!num)
		terminate(data, ERR_MALLOC, 1);
	res = malloc(sizeof(char) + (size + 1));
	if (!res)
		terminate(data, ERR_MALLOC, 1);
	copy_shlvl_env(res, str, num);
	free(num);
	free(str);
	return (res);
}

static	void	refrech_shlvl(t_data *data)
{
	t_env	*current;

	current = data->env;
	while (current)
	{
		if (ft_strncmp(current->value, "SHLVL=", 5) == 0)
		{
			current->value = get_new_shlvl(data, current->value);
			return ;
		}
		current = current->next;
	}
	terminate(data, "command not found\n", 127);
}

int	env_init(t_data *data, char **env_array)
{
	int		i;

	if (!env_array || !env_array[0])
		return (0);
	i = 0;
	while (env_array[i])
	{
		if (!ft_env_lstadd_back(&data->env,
				ft_env_lstnew(ft_strdup(env_array[i]))))
			terminate(data, ERR_MALLOC, 1);
		i++;
	}
	refrech_shlvl(data);
	return (i);
}
