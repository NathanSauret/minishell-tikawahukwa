/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct_fill.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:16:46 by j_sk8             #+#    #+#             */
/*   Updated: 2024/11/05 16:37:52 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_operator(char *str)
{
	if (ft_strnstr((str), "<<", 2))
		return (1);
	else if (ft_strnstr((str), ">>", 2))
		return (1);
	if (ft_strnstr((str), "<", 1))
		return (1);
	else if (ft_strnstr((str), ">", 1))
		return (1);
	else if (ft_strnstr((str), "|", 1))
		return (1);
	return (0);
}

int	fill_cmd(t_cmd *cmd, t_token *token)
{
	int		i;
	int		y;
	t_token	*tmp;

	tmp = token;
	i = 0;
	y = 0;
	cmd->tokens = token;
	while (i < token->cmd_line_size)
	{
		if (is_operator(tmp->str) && (i + 2) != token->cmd_line_size)
		{
			tmp = tmp->next->next;
			i += 2;
			continue ;
		}
		else if (is_operator(tmp->str) && (i + 2) >= token->cmd_line_size)
			break ;
		cmd->cmd[y] = token->command_line[i];
		y++;
		i++;
		tmp = tmp->next;
	}
	cmd->cmd[y] = NULL;
	return (1);
}

int	parse_cmd(t_data *data, t_token *token)
{
	t_cmd	*new_cmd;
	t_token	*tmp;

	tmp = token;
	new_cmd = ft_cmd_lstnew(NULL);
	if (!tmp)
		return (0);
	new_cmd->cmd = malloc(sizeof(char *) * (token->cmd_line_size + 1));
	if (!new_cmd->cmd)
		return (0);
	fill_cmd(new_cmd, token);
	while (token && token->type != CMD)
		token = token->next;
	if (!token->is_builtin)
		new_cmd->path = ft_strdup(token->path);
	else
		new_cmd->is_builtin = 1;
	return (ft_cmd_lstadd_back(&(data->cmd), new_cmd));
}

int	fill_cmd_struct(t_data *data)
{
	int		i;
	t_token	*tmp;

	tmp = data->token;
	i = 0;
	if (data->num_of_pipe > 0)
	{
		while (i < data->num_of_pipe)
		{
			if (!parse_cmd(data, tmp))
				return (0);
			while (tmp && tmp->type != PIPE)
				tmp = tmp->next;
			tmp = tmp->next;
			i++;
		}
	}
	if (!parse_cmd(data, tmp))
		return (0);
	return (1);
}
