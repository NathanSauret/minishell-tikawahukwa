/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 21:38:42 by j_sk8             #+#    #+#             */
/*   Updated: 2024/10/17 23:48:07 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_shell_level()
{
	char *shlvl = getenv("SHLVL");
	if (shlvl)
	{
		return (ft_atoi(shlvl));
	}
	return (0);
}

int	line_is_empty(char *str)
{
	while (*str)
	{
		if (!(ft_is_space(*str)))
			return (0);
		str++;
	}
	return (1);
}

int	add_cmd(t_token **token, char *str, int type)
{
	if (!str)
		return (printf(ERR_MALLOC), 0);
	if (!(ft_token_lstadd_back(token, ft_token_lstnew(str, type))))
		return (printf(ERR_MALLOC), 0);
	return (1);
}

int	get_cmd(t_data *data, char *str)
{
	if (ft_strstr(str, "echo", 4))
		return (add_cmd(&(data->token), ft_substr(str, 0, 4), CMD));
	else
		return (printf("syntax error\n"), 0);
}

int	get_arg(t_data *data, char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (!(ft_is_space(str[len])))
		len++;
	return (add_cmd(&(data->token), ft_substr(&str[i], 0, len), ARG));
}

int	parsing(t_data *data)
{
	int		i;

	i = 0;
	while (ft_is_space(data->input[i]))
		i++;
	if (!(get_cmd(data, &data->input[i])))
		return (0);
	i += ft_strlen(data->token->str);
	while (ft_is_space(data->input[i]))
		i++;
	if (!(get_arg(data, &data->input[i])))
		return (0);
	//data->token = data->token->next;
	return (1);

}

void	data_init(t_data *data)
{
	data->arg = NULL;
	data->token = NULL;
	data->input = NULL;
	data->env = NULL;
	data->tok = NULL;
}

void	print_token(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp->next != token)
	{
		printf("Type : %d, [%s]\n", tmp->type, tmp->str);
		tmp = tmp->next;
	}
	printf("Type : %d, [%s]\n",  tmp->type, tmp->str);
}

char	**tokens_to_args(t_token *token_list)
{
	int		count;
	char	**args;
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = token_list;
	count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
		if (tmp == token_list)
			break;
	}
	args = malloc((count + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	tmp = token_list;
	while (i < count)
	{
		args[i] = tmp->str;
		tmp = tmp->next;
		i++;
	}
	args[count] = NULL;
	return (args);
}

void	print_3d(char **str)
{
	int	i = 0;

	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	int		i;
	char	*exec_path;

	(void)argc;
	(void)argv;
	data_init(&data);
	env_init(&data, env);
	while (1)
	{
		data.input = readline("minishell> ");
		if (data.input == NULL)
			return (exit_error2(&data, "exit..\n"));
		add_history(data.input);
		if (line_is_empty(data.input))
			continue ;
		if (!parsing(&data))
			continue ;
		data.tok = strtok(data.input, " ");
		i = 0;
		while (data.tok != NULL && i < MAX_ARGS - 1)
		{
			data.args[i++] = data.tok;
			data.tok = strtok(NULL, " ");
		}
		data.args[i] = NULL;
		/*data.arg = tokens_to_args(data.token);
		if (!data.arg)
		{
			printf(ERR_MALLOC);
			ft_token_lstclear(&(data.token));
			continue ;
		}*/
		data.pid = fork();
		if (data.pid < 0)
		{
			perror("fork");
			free(data.input);
			free_env(data.env);
			exit(EXIT_FAILURE);
		}
		//print_3d(data.args);
		if (data.pid == 0)
		{
			exec_path = get_ex_path(data.args[0], &data);
			//printf("path %s\n", data.args[0]);
			if (exec_path)
			{
				execve(exec_path, data.args, env);
				perror("execve");
				free(exec_path);
			}
			else
				fprintf(stderr, "Command not found: %s\n", data.args[0]);
			exit(EXIT_FAILURE);
		}
		else
			wait(NULL);
		free_token(&data);
	}
	free_env(data.env);
	return 0;
}
