/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 22:51:43 by jmiccio           #+#    #+#             */
/*   Updated: 2024/10/14 21:02:59 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strchr(char const *str, int c)
{
	while (*str)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if (*str == (char)c)
		return ((char *)str);
	else
		return (NULL);
}
