/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:15:41 by nsauret           #+#    #+#             */
/*   Updated: 2024/10/28 18:04:03 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	exec_builtin(t_data *data)
{
	if (ft_strnstr((data->token->str), "exit", 4))
		return (ft_exit(data));
	/*if (ft_strnstr((data->token->str), "cd", 2))
		return (ft_cd(data));
	if (ft_strnstr((data->token->str), "echo", 4))
		return (ft_echo(data));
	if (ft_strnstr((data->token->str), "env", 3))
		return (ft_env(data));
	if (ft_strnstr((data->token->str), "env", 3))
		return (ft_env(data));
	if (ft_strnstr((data->token->str), "export", 6))
		return (ft_export(data));
	if (ft_strnstr((data->token->str), "pwd", 3))
		return (ft_pwd(data));
	if (ft_strnstr((data->token->str), "unset", 5))
		return (ft_unset(data));*/
	ft_printf("YOU FORGOT A F*CKING BUILTIN FUNCTION, YOU DUMBA**!\n");
	return (0);
}

int	exec(t_data *data, char **env)
{
	if (data->token->is_builtin)
		return (exec_builtin(data));
	else
		pipex(data, env);
	return (1);
}
