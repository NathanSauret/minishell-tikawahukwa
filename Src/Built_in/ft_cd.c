/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:37:43 by j_sk8             #+#    #+#             */
/*   Updated: 2025/01/07 10:01:46 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

static int	export(t_data *data, char *str)
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

void	refresh_oldpwd_var(t_data *data, char *oldpwd)
{
	char	*cpy;

	cpy = ft_strjoin(ft_strdup("OLDPWD="), oldpwd);
	if (!cpy)
		terminate(data, ERR_MALLOC, 1);
	if (!export(data, cpy))
	{
		free(cpy);
		terminate(data, ERR_MALLOC, 1);
	}
	free(cpy);
}

void	refresh_pwds(t_data *data, char *oldpwd)
{
	char	*res;

	refresh_oldpwd_var(data, oldpwd);
	res = ft_strjoin(ft_strdup("PWD="), getcwd(NULL, 0));
	if (!res)
		terminate (data, ERR_MALLOC, 1);
	if (!export(data, res))
	{
		free(res);
		terminate (data, ERR_MALLOC, 1);
	}
	free(res);
}

int	ft_cd(t_data *data, t_env *env, char **args)
{
	char	*curr_pwd;

	curr_pwd = getcwd(NULL, 0);
	if (args[1] == NULL)
	{
		if (!ft_getenv(env, "HOME") || chdir(ft_getenv(env, "HOME")) != 0)
		{
			perror("cd");
			return (free(curr_pwd), 1);
		}
	}
	else if (args[2])
	{
		ft_printerr("~ Tikawahukwa: cd : too many arguments\n");
		return (free(curr_pwd), 1);
	}
	else if (chdir(args[1]) != 0)
	{
		perror("~ Tikawahukwa: cd");
		return (free(curr_pwd), 1);
	}
	refresh_pwds(data, curr_pwd);
	return (0);
}
