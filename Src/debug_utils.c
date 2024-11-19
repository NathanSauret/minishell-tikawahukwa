/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:13:40 by j_sk8             #+#    #+#             */
/*   Updated: 2024/11/19 18:38:56 by j_sk8            ###   ########.fr       */
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

void	print_token(t_token *token, int show_args)
{
	t_token	*tmp;

	tmp = token;
	while (token->next)
	{
		printf("Type : %d, [%s]\n", token->type, token->str);
		token = token->next;
	}
	printf("Type : %d, [%s]\n", token->type, token->str);
	if (show_args)
		show_command_line(tmp);
}

char	*ft_getenv(t_env *env, char *str)
{
	char	*ptr;
	int		size;

	size = ft_strlen(str);
	ptr = NULL;
	while (env)
	{
		if (!ft_strncmp(env->value, str, size)
			&& (env->value[size] == '=' || env->value[size] == '\0'))
			{
				ptr = &env->value[size + 1];
				return(ptr);
			}
			env = env->next;
	}
	return (ptr);
}

int	exec_test(char *str, t_data *data, char **env)
{
	data->input = ft_strdup(str);
	if (data->input == NULL)
		return (printf("exit..\n"), 1);
	if (!parsing(data))
		return (0);
	exec(data, env);
	printf("env = [%s]\n", ft_getenv(data->env, "PATH"));
	free_token(data);
	return (1);
}
