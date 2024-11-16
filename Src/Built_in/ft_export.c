/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:59:22 by jmiccio           #+#    #+#             */
/*   Updated: 2024/11/16 17:37:18 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	export_wihtout_args(t_env *lst, int env_len)
{
	char	**env;

	printf("check\n");
	env = lst_to_arr(lst, env_len);
	if (!env)
		return (0);
	sort_array(env, env_len);
	print_array(env);
	free(env);
	return (1);
}

int	ft_export(char **str, t_data *data)
{

	if (!str || !str[1])
	{
		if (!export_wihtout_args(data->env, data->env_len))
			return (print_error(ERR_MALLOC));
		return (0);
	}
	return (0);
}
