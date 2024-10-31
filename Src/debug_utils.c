/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:13:40 by j_sk8             #+#    #+#             */
/*   Updated: 2024/10/31 15:20:56 by j_sk8            ###   ########.fr       */
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
		printf(" infile: %d, outfile: %d, cmd : ", tmp->infile, tmp->outfile);
		print_tab(tmp->cmd);
		printf("\n");
		tmp = tmp->next;
	}
	printf(" infile: %d, outfile: %d, cmd : ",
		tmp->infile, tmp->outfile);
	print_tab(tmp->cmd);
	printf("\n");
}

void	print_token(t_token *token, int show_args)
{
	t_token	*tmp;

	tmp = token;
	while (token->next)
	{
		printf("path: %s Type : %d, [%s]\n", token->path, token->type, token->str);
		token = token->next;
	}
	printf("path: %s Type : %d, [%s]\n", token->path, token->type, token->str);
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
