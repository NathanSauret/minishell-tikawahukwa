/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 20:32:05 by j_sk8             #+#    #+#             */
/*   Updated: 2024/12/16 23:46:57 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strstr(const char *str, const char *cmp)
{
	const char	*h;
	const char	*h_ptr;
	const char	*n_ptr;

	if (*cmp == '\0')
		return ((char *)str);
	h = str;
	while (*h != '\0')
	{
		h_ptr = h;
		n_ptr = cmp;
		while (*h_ptr == *n_ptr && *n_ptr != '\0')
		{
			h_ptr++;
			n_ptr++;
		}
		if (*n_ptr == '\0')
			return ((char *)h);
		h++;
	}
	return (NULL);
}
