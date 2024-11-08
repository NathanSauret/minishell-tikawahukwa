/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:47:54 by j_sk8             #+#    #+#             */
/*   Updated: 2024/11/08 12:45:48 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

int	add_cmd(t_data *data, char *str, int type)
{
	if (!str)
		return (printf(ERR_MALLOC), 0);
	if (!(ft_token_lstadd_back(&(data->token), ft_token_lstnew(str, type))))
		return (printf(ERR_MALLOC), 0);
	return (1);
}

int	get_arg(t_data *data, char **str)
{
	int		len;
	int		start;
	int		type;
	int		space;
	t_token	*tmp;

	tmp = ft_token_lstlast(data->token);
	space = 1;
	start = 0;
	len = token_len(*str, &start, &space, tmp);
	if (!len)
		return ((*str) += 1, 1);
	len = get_type(data->token, *str, &type, len);
	if (!space && tmp && !is_operator(tmp->str))
	{
		tmp->str = ft_strjoin(tmp->str, ft_substr(*str, start, len));
		if (!tmp->str)
			return (0);
	}
	else
		if (!(add_cmd(data, ft_substr(*str, start, len), type)))
			return (0);
	if (is_quote(*(*str)))
		(*str) += len + 2;
	else
		(*str) += len;
	return (1);
}

int	add_token(t_data *data)
{
	char	*cmd;

	cmd = data->input;
	while (*cmd)
	{
		while (*cmd && (ft_is_space(*cmd)))
			cmd++;
		if (*cmd && !(get_arg(data, &cmd)))
			return (0);
		if (ft_token_lstlast(data->token)->type == PIPE)
			data->num_of_pipe += 1;
	}
	return (1);
}
