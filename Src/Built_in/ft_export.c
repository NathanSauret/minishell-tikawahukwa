/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:59:22 by jmiccio           #+#    #+#             */
/*   Updated: 2024/11/21 19:38:51 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	export_without_args(t_env *lst, int env_len)
{
	char	**env;
	int		i;
	int		y;

	i = 0;
	env = lst_to_arr(lst, env_len);
	if (!env)
		return (0);
	sort_array(env, env_len);
	while (env[i])
	{
		y = 0;
		ft_printf("declare -x ");
		while (env[i][y] && env[i][y] != '=')
			ft_printf("%c", env[i][y++]);
		if (env[i][y] == '=')
			ft_printf("=\"%s\"\n", &env[i][y + 1]);
		else
			ft_printf("\n");
		i++;
	}
	free(env);
	return (1);
}

int	exist2(t_env *env, char *str)
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

int	export_with_args(t_data *data, char *str)
{
	t_env	*tmp;
	t_env	*new;
	int		res;

	res = exist(data->env, str);
	if (res == -1)
		return (0);
	else if (res)
		return (1);
	else
	{
		tmp = data->env;
		while (tmp->next != NULL)
			tmp = tmp->next;
		new = malloc(sizeof(t_env));
		if (!new)
			return (0);
		new->value = ft_strdup(str);
		if (!new->value)
			return (0);
		tmp->next = new;
		new->next = NULL;
		data->env_len += 1;
	}
	return (1);
}

int	syntax_parsing(char *str)
{
	int	i;

	i = 0;
	if (str[i] && (!ft_isalpha(str[i]) && str[i] != '_'))
		return (0);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_export(char **str, t_data *data)
{
	if (!str || !str[1])
	{
		if (!export_without_args(data->env, data->env_len))
			return (print_error(ERR_MALLOC));
		return (0);
	}
	else
	{
		if (!syntax_parsing(str[1]))
			return (print_error("export: invalid identifier\n"));
		if (!export_with_args(data, str[1]))
			return (print_error(ERR_MALLOC));
		return (0);
	}
	return (0);
}
