/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:59:22 by jmiccio           #+#    #+#             */
/*   Updated: 2024/11/17 18:24:40 by jmiccio          ###   ########.fr       */
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

t_env	*exist(t_env *env, char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	while (env)
	{
		if (!ft_strncmp(env->value, str, i)
			&& (env->value[i] == '=' || env->value[i] == '\0'))
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	export_with_args(t_data *data, char *str)
{
	t_env	*tmp;
	t_env	*new;

	tmp = exist(data->env, str);
	if (tmp)
	{
		if (!ft_strnstr(tmp->value, "=", ft_strlen(tmp->value)))
			return (1);
		free(tmp->value);
		tmp->value = ft_strdup(str);
		if (!tmp->value)
			return (0);
	}
	else if (tmp == NULL)
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
