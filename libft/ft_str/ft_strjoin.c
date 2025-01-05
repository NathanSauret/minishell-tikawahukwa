/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:57:18 by jmiccio           #+#    #+#             */
/*   Updated: 2025/01/05 23:13:44 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	total_len;
	char	*str;

	if (!s1 || !s2)
	{
		if (s1)
			free(s1);
		if (s2)
			free(s2);
		return (NULL);
	}
	total_len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc((sizeof(char) * total_len + 1));
	if (!str)
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	ft_memcpy(str, s1, ft_strlen(s1));
	ft_memcpy(str + ft_strlen(s1), s2, ft_strlen(s2));
	str[total_len] = '\0';
	free(s1);
	free(s2);
	return (str);
}
