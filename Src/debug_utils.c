/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:13:40 by j_sk8             #+#    #+#             */
/*   Updated: 2024/10/28 19:11:15 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	show_command_line(t_token *token)
{
	int		arg_num;
	int		i;

	i = 0;
	arg_num = 1;
	while (token)
	{
		if (token->command_line)
		{
			while (token->command_line[i])
			{
				printf("arg num%d: %s\n", arg_num, token->command_line[i]);
				i++;
			}
			i = 0;
			arg_num++;
		}
		token = token->next;
	}
}

void	print_token(t_token *token, int show_args)
{
	t_token	*tmp;

	tmp = token;
	test_func();
	while (token->next)
	{
		printf("Type : %d, [%s]\n", token->type, token->str);
		token = token->next;
	}
	printf("Type : %d, [%s]\n", token->type, token->str);
	if (show_args)
		show_command_line(tmp);
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
