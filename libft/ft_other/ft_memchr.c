/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 23:34:09 by jmiccio           #+#    #+#             */
/*   Updated: 2024/10/14 21:02:13 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*ptr;

	ptr = ((const unsigned char *)s);
	i = 0;
	while (i < n)
	{
		if (ptr[i] == ((unsigned char)c))
			return ((void *)(ptr + i));
		i++;
	}
	return (NULL);
}
