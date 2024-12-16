/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:37:43 by j_sk8             #+#    #+#             */
/*   Updated: 2024/12/08 15:37:49 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*supp_last_dir(char *str)
{
	int		last_bs;
	int		i;
	char	*res;

	i = 0;
	last_bs = 0;
	while (str[i])
	{
		if (str[i] == '/')
			last_bs = i;
		i++;
	}
	res = ft_strndup(str, last_bs);
	free(str);
	if (!res)
		return (NULL);
	return (res);
}

void	refresh_oldpwd_var(t_data *data, t_env *env, char *arg)
{
	char	**cpy;

	(void) arg;
	cpy = malloc(sizeof(char *) * 3);
	if (!cpy)
		terminate(data, ERR_MALLOC, 1);
	cpy[0] = ft_strdup("export");
	if (!cpy[0])
		terminate(data, ERR_MALLOC, 1);
	cpy[1] = ft_strjoin(ft_strdup("OLDPWD="), ft_strdup(ft_getenv(env, "PWD")));
	if (!cpy[1])
		terminate(data, ERR_MALLOC, 1);
	cpy[2] = NULL;
	ft_export(cpy, data);
	free_array(cpy);
}

void	refresh_pwd_var(t_data *data, t_env *env, char *arg)
{
	char	**cpy;
	char	*tmp;

	cpy = malloc(sizeof(char *) * 3);
	if (!cpy)
		terminate(data, ERR_MALLOC, 1);
	cpy[0] = ft_strdup("export");
	if (!cpy[0])
		terminate(data, ERR_MALLOC, 1);
	cpy[1] = ft_strjoin(ft_strdup("PWD="), ft_strdup(ft_getenv(env, "PWD")));
	if (!cpy[1])
		terminate(data, ERR_MALLOC, 1);
	if (ft_strncmp("..", arg, MAX_LENGTH))
	{
		tmp = ft_strjoin(ft_strdup("/"), ft_strdup(arg));
		cpy[1] = ft_strjoin(cpy[1], tmp);
	}
	else
		cpy[1] = supp_last_dir(cpy[1]);
	if (!cpy[1])
		terminate(data, ERR_MALLOC, 1);
	cpy[2] = NULL;
	ft_export(cpy, data);
	free_array(cpy);
}

void	refresh_pwds(t_data *data, t_env *env, char *arg)
{
	if (ft_strlen(ft_getenv(env, "PWD")) < 2
		|| ft_strlen(ft_getenv(env, "OLDPWD")) < 2)
		ft_printerr("~ Tikawahukwa: cd: $OLDPWD error\n");
	else
		refresh_oldpwd_var(data, env, arg);
	if (ft_strlen(ft_getenv(env, "PWD")) < 2)
		ft_printerr("~ Tikawahukwa: cd: $PWD error\n");
	else
		refresh_pwd_var(data, env, arg);
}

int	ft_cd(t_data *data, t_env *env, char **args)
{
	char	*home;

	home = ft_getenv(env, "HOME");
	if (args[1] == NULL)
	{
		if (home == NULL || chdir(home) != 0)
		{
			perror("cd");
			return (1);
		}
	}
	if (args[2])
	{
		ft_printerr("~ Tikawahukwa: cd : too many arguments\n");
		return (1);
	}
	if (chdir(args[1]) != 0)
	{
		perror("~ Tikawahukwa: cd");
		return (1);
	}
	refresh_pwds(data, env, args[1]);
	return (0);
}
