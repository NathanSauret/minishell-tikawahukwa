/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:17:08 by jmiccio           #+#    #+#             */
/*   Updated: 2024/10/14 21:03:02 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *s)
{
	char	*str;
	int		size;
	int		i;

	size = ft_strlen(s);
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < size)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
