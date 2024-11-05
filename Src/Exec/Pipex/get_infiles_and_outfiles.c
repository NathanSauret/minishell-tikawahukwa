/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infiles_and_outfiles.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 17:23:37 by nsauret           #+#    #+#             */
/*   Updated: 2024/11/03 17:37:07 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	get_infiles_and_outfiles(t_data *data)
{
	t_token	*token;

	token = data->token;
	while (token)
	{
		if (token->type == INPUT)
			ft_printf("input: %s\n", token->str);
		if (token->type == TRUNC)
			ft_printf("trunc: %s\n", token->str);
		if (token->type == APPEND)
			ft_printf("append: %s\n", token->str);
		if (token->type == APPEND)
			ft_printf("append: %s\n", token->str);
		token = token->next;
	}
	return (1);
}
