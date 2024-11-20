/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:05:51 by nsauret           #+#    #+#             */
/*   Updated: 2024/11/20 17:42:50 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*join;
	int		len1;
	int		len2;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen((char *)s1);
	len2 = ft_strlen((char *)s2);
	join = malloc(sizeof(char) * len1 + len2 + 1);
	if (!join)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		join[i] = s1[i];
		i++;
	}
	while (i < len1 + len2)
	{
		join[i] = s2[i - len1];
		i++;
	}
	join[i] = '\0';
	return (free(s1), join);
}
