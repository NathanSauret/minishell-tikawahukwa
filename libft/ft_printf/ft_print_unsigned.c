/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:23:05 by nsauret           #+#    #+#             */
/*   Updated: 2024/10/14 21:54:18 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	get_unsigned_len(unsigned int el)
{
	int	len;

	if (el == 0)
		return (1);
	len = 0;
	if ((int)el < 0)
	{
		el *= -1;
		len ++;
	}
	while (el > 0)
	{
		el /= 10;
		len++;
	}
	return (len);
}

int	ft_print_unsigned(unsigned int el)
{
	char	*str_el;

	str_el = ft_itoa(el);
	ft_print_str(str_el);
	free(str_el);
	return (get_unsigned_len(el));
}
