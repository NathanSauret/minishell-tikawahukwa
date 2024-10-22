/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 23:27:39 by j_sk8             #+#    #+#             */
/*   Updated: 2024/10/21 14:18:02 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_array(char	**array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_token(t_data *data)
{
	free(data->input);
	if (data->token)
		ft_token_lstclear(&(data->token));
	if (data->arg)
		free(data->arg);
	data->arg = NULL;
}

int	is_error(char *str, t_data *data)
{
	printf("%s", str);
	free_token(data);
	return (0);
}
