/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:13:40 by j_sk8             #+#    #+#             */
/*   Updated: 2024/10/27 23:22:18 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_token(t_token *token, int show_args)
{
	int		i;
	int		arg_num;
	t_token	*tmp;

	arg_num = 1;
	tmp = token;
	i = 0;
	while (token->next)
	{
		printf("Type : %d, [%s]\n", token->type, token->str);
		token = token->next;
	}
	printf("Type : %d, [%s]\n", token->type, token->str);
	if (show_args)
	{
		while (tmp)
		{
			if (tmp->command_line)
			{
				while (tmp->command_line[i])
				{
					printf("arg num%d: %s\n", arg_num, tmp->command_line[i]);
					i++;
				}
				i = 0;
				arg_num++;
			}
			tmp = tmp->next;
		}
	}
}

void	print_3d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
}
