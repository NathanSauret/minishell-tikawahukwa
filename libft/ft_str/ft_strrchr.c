/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 23:08:51 by jmiccio           #+#    #+#             */
/*   Updated: 2024/10/14 21:03:32 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char		*last;
	const char		*ptr;
	unsigned char	target;

	ptr = s;
	last = NULL;
	target = (char)c;
	while (*ptr)
	{
		if (*ptr == target)
			last = ptr;
		ptr++;
	}
	if (target == '\0')
		return ((char *)ptr);
	return ((char *)last);
}
