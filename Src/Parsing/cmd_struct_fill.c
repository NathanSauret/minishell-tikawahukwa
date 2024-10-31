/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct_fill.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:16:46 by j_sk8             #+#    #+#             */
/*   Updated: 2024/10/31 14:57:08 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_open(t_cmd *cmd, char *arg)
{
	cmd->infile = open(arg, O_RDONLY, 0644);
	if (cmd->infile < 0)
		return (0);
	return (1);
}

int	get_file(t_cmd *cmd, t_token *token)
{
	if (token->type == INPUT)
	{
		if (!token->next || !ft_open(cmd, token->next->str))
			return (0);
		cmd->cmd = malloc(sizeof(char *) * 2);
		if (!(cmd->cmd))
			return (0);
		cmd->cmd[0] = token->command_line[2];
		cmd->cmd[1] = NULL;
		while (token->type != CMD)
			token = token->next;
		if (token->is_builtin != 1)
			cmd->path = ft_strdup(token->path);
		else
			cmd->is_builtin = 1;
	}
	return (1);
}

int	fill_cmd(t_cmd *cmd, t_token *token, int size)
{
	int	i;

	i = 0;
	cmd->cmd = malloc(sizeof(char *) * (size + 1));
	if (!(cmd->cmd))
		return (0);
	while (i < size)
	{
		cmd->cmd[i] = token->command_line[i];
		i++;
	}
	if (!token->is_builtin)
		cmd->path = ft_strdup(token->path);
	else
		cmd->is_builtin = 1;
	cmd->cmd[i] = NULL;
	return (1);
}

int	parse_cmd(t_data *data, t_token *token)
{
	t_cmd	*new_cmd;
	t_token	*tmp;
	int		i;

	tmp = token;
	new_cmd = ft_cmd_lstnew(NULL, -2, -2);
	if (!tmp)
		return (0);
	i = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (i == 0 && is_operator(tmp->str))
		{
			if (!get_file(new_cmd, tmp))
				return (0);
			return (ft_cmd_lstadd_back(&(data->cmd), new_cmd));
		}
		i++;
		tmp = tmp->next;
	}
	fill_cmd(new_cmd, token, i);
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
