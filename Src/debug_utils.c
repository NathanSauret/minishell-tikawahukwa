/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:13:40 by j_sk8             #+#    #+#             */
/*   Updated: 2024/12/11 10:54:00 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_tab(char **tab)
{
	int	i;

	if (!(tab))
	{
		printf("NULL");
		return ;
	}
	i = 0;
	printf("[");
	while (tab[i])
	{
		printf("%s", tab[i]);
		if (tab[i + 1])
			printf(", ");
		i++;
	}
	printf("]");
}

void	print_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	if (!cmd)
		return ;
	while (tmp->next)
	{
		printf("token head [%s], cmd :", tmp->tokens->str);
		print_tab(tmp->cmd);
		printf("\n");
		tmp = tmp->next;
	}
	printf(" ");
	printf("token head [%s], cmd :", tmp->tokens->str);
	print_tab(tmp->cmd);
	printf("\n");
}

void	print_token(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (token)
	{
		while (token->next)
		{
			printf("Type : %d, [%s]\n", token->type, token->str);
			token = token->next;
		}
		printf("Type : %d, [%s]\n", token->type, token->str);
	}
}

