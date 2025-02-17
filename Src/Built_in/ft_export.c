/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:59:22 by jmiccio           #+#    #+#             */
/*   Updated: 2025/01/07 10:02:15 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	export_without_args(t_data *data, t_env *lst, int env_len)
{
	char	**env;
	int		i;
	int		y;

	i = 0;
	env = lst_to_arr(data, lst, env_len);
	sort_array(env, env_len);
	while (env[i])
	{
		y = 0;
		ft_printf("declare -x ");
		while (env[i][y] && env[i][y] != '=')
			write(1, &env[i][y++], 1);
		if (env[i][y] == '=')
			ft_printf("=\"%s\"\n", &env[i][y + 1]);
		else
			ft_printf("\n");
		i++;
	}
	free(env);
	return (1);
}

static int	exist(t_env *env, char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	while (env)
	{
		if (!ft_strncmp(env->value, str, i)
			&& (env->value[i] == '=' || env->value[i] == '\0'))
			break ;
		env = env->next;
	}
	if (!env)
		return (0);
	if (!ft_strnstr(str, "=", ft_strlen(str)))
		return (1);
	free(env->value);
	env->value = ft_strdup(str);
	if (!env->value)
		return (-1);
	return (1);
}

static int	export_with_args(t_data *data, char *str)
{
	int		res;

	res = exist(data->env, str);
	if (res == -1)
		return (0);
	else if (res)
		return (1);
	if (!ft_env_lstadd_back(&data->env,
			ft_env_lstnew(ft_strdup(str))))
		return (0);
	data->env_len += 1;
	return (1);
}

static int	syntax_parsing(char *str)
{
	int	i;

	i = 0;
	if (str[i] && (!ft_isalpha(str[i]) && str[i] != '_'))
	{
		ft_printerr("Tikawahukwa ☕: export: not a valid identifier\n");
		return (0);
	}
	i++;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			ft_printerr("Tikawahukwa ☕: export: not a valid identifier\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_export(char **str, t_data *data)
{
	int	i;
	int	exit_status;

	exit_status = 0;
	i = 1;
	if ((!str || !str[1]) && data->env_len > 0)
	{
		export_without_args(data, data->env, data->env_len);
		return (exit_status);
	}
	else
	{
		while (str[i])
		{
			if (!syntax_parsing(str[i]))
				exit_status = 1;
			else if (!export_with_args(data, str[i]))
				terminate(data, ERR_MALLOC, 0);
			i++;
		}
	}
	return (exit_status);
}
