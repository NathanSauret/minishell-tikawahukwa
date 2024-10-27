/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:47:54 by j_sk8             #+#    #+#             */
/*   Updated: 2024/10/27 22:25:33 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
		tmp->str = ft_strjoin(tmp->str, ft_substr(*str, start, len));
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
