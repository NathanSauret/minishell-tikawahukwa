/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printerr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:13:31 by j_sk8             #+#    #+#             */
/*   Updated: 2024/12/09 10:40:05 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

#include <stdarg.h>
#include <unistd.h>

static void	ft_putstr(const char *s, int *count)
{
	if (!s)
		s = "(null)";
	while (*s)
	{
		write(2, s++, 1);
		(*count)++;
	}
}

static void	ft_putnbr(int n, int *count)
{
	char	c;

	if (n == -2147483648)
	{
		ft_putstr("-2147483648", count);
		return ;
	}
	if (n < 0)
	{
		write(2, "-", 1);
		(*count)++;
		n = -n;
	}
	if (n > 9)
		ft_putnbr(n / 10, count);
	c = (n % 10) + '0';
	write(2, &c, 1);
	(*count)++;
}

static void	ft_puthex(unsigned int n, int *count)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (n >= 16)
		ft_puthex(n / 16, count);
	write(2, &hex[n % 16], 1);
	(*count)++;
}

static void	ft_handle_format(const char **format, va_list args, int *count)
{
	if (**format == 's')
		ft_putstr(va_arg(args, char *), count);
	else if (**format == 'd')
		ft_putnbr(va_arg(args, int), count);
	else if (**format == 'x')
		ft_puthex(va_arg(args, unsigned int), count);
	else
	{
		write(2, *format, 1);
		(*count)++;
	}
}

int	ft_printerr(const char *format, ...)
{
	va_list	args;
	int		count;

	count = 0;
	write(2, "\033[1;31m", 7);
	va_start(args, format);
	while (*format)
	{
		if (*format == '%' && *(format + 1))
		{
			format++;
			ft_handle_format(&format, args, &count);
		}
		else
		{
			write(2, format, 1);
			count++;
		}
		format++;
	}
	va_end(args);
	write(2, "\033[0m", 4);
	return (count);
}
