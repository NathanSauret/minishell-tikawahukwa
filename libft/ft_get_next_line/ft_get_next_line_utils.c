/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:05:51 by nsauret           #+#    #+#             */
/*   Updated: 2024/10/14 22:14:48 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"

void	*ft_calloc(size_t ft_nmemb, size_t ft_size)
{
	char	*ptr;
	size_t	total_size;
	size_t	i;

	if (ft_nmemb == 0 || ft_size == 0)
		return (malloc(0));
	total_size = ft_nmemb * ft_size;
	if (total_size / ft_size != ft_nmemb)
		return (NULL);
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < total_size)
		ptr[i++] = '\0';
	return (ptr);
}

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
