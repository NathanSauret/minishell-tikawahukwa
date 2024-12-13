/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:13:40 by j_sk8             #+#    #+#             */
/*   Updated: 2024/12/12 15:07:01 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_tab(char **tab)
{
	int	i;

	if (!(tab))
	{
		ft_printf("NULL");
		return ;
	}
	i = 0;
	ft_printf("[");
	while (tab[i])
	{
		ft_printf("%s", tab[i]);
		if (tab[i + 1])
			ft_printf(", ");
		i++;
	}
	ft_printf("]");
}

void	print_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	if (!cmd)
		return ;
	while (tmp->next)
	{
		ft_printf("token head [%s], cmd :", tmp->tokens->str);
		print_tab(tmp->cmd);
		ft_printf("\n");
		tmp = tmp->next;
	}
	ft_printf(" ");
	ft_printf("token head [%s], cmd :", tmp->tokens->str);
	print_tab(tmp->cmd);
	ft_printf("\n");
}

void	print_token(t_token *token)
{
	if (token)
	{
		while (token->next)
		{
			ft_printf("Type : %d, [%s]\n", token->type, token->str);
			token = token->next;
		}
		ft_printf("Type : %d, [%s]\n", token->type, token->str);
	}
}
