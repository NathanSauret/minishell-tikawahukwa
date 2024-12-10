/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printerr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:13:31 by j_sk8             #+#    #+#             */
/*   Updated: 2024/12/10 17:34:05 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

#include <stdarg.h>
#include <unistd.h>

static void	ft_putstr(const char *s, int *count, char res[MAX_LENGTH])
{
	if (!s)
		s = "(null)";
	while (*s)
	{
		res[*count] = *s;
		(*count)++;
		s++;
	}
}

static void	ft_putnbr(int n, int *count, char res[MAX_LENGTH])
{
	char	c;

	if (n == -2147483648)
	{
		ft_putstr("-2147483648", count, res);
		return ;
	}
	if (n < 0)
	{
		res[*count] = '-';
		(*count)++;
		n = -n;
	}
	if (n > 9)
		ft_putnbr(n / 10, count, res);
	c = (n % 10) + '0';
	res[*count] = c;
	(*count)++;
}

static void	ft_puthex(unsigned int n, int *count, char res[MAX_LENGTH])
{
	char	*hex;

	hex = "0123456789abcdef";
	if (n >= 16)
		ft_puthex(n / 16, count, res);
	res[*count] = hex[n % 16];
	(*count)++;
}

static void	ft_handle_str(const char **str, va_list args, int *count, char res[MAX_LENGTH])
{
	if (**str == 's')
		ft_putstr(va_arg(args, char *), count, res);
	else if (**str == 'd')
		ft_putnbr(va_arg(args, int), count, res);
	else if (**str == 'x')
		ft_puthex(va_arg(args, unsigned int), count,res);
	else
	{
		write(2, *str, 1);
		(*count)++;
	}
}

int	ft_printerr(const char *str, ...)
{
	va_list	args;
	int		count;
	char	res[MAX_LENGTH];

	ft_bzero(res, MAX_LENGTH);
	count = 0;
	ft_putstr("\033[1;31m",&count, res);
	va_start(args, str);
	while (*str)
	{
		if (*str == '%' && *(str + 1))
		{
			str++;
			ft_handle_str(&str, args, &count, res);
		}
		else
		{
			res[count] = *str;
			count++;
		}
		str++;
	}
	va_end(args);
	res[count] = '\0';
	ft_putstr("\033[0m",&count, res);
	write(2, res, ft_strlen(res));
	return (count);
}
