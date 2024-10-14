/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:28:03 by jmiccio           #+#    #+#             */
/*   Updated: 2024/10/14 21:03:12 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dest_length;
	size_t	src_length;

	if ((!dst || !src) && !size)
		return (0);
	dest_length = ft_strlen(dst);
	src_length = ft_strlen(src);
	if (dest_length >= size)
		return (size + src_length);
	j = dest_length;
	i = 0;
	while (src[i] && dest_length + i < size - 1)
	{
		dst[j] = src[i];
		j++;
		i++;
	}
	dst[j] = '\0';
	return (dest_length + src_length);
}
