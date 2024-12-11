/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:57:50 by nsauret           #+#    #+#             */
/*   Updated: 2024/12/11 11:51:16 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

#include <stdarg.h>
#include <unistd.h>

static void	ft_putstr(const char *s, int *count, char res[MAX_LENGTH])
{
	if (!s)
		s = "(null)";
	while (*s && *count < MAX_LENGTH - 1)
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
	if (n < 0 && *count < MAX_LENGTH - 1)
	{
		res[*count] = '-';
		(*count)++;
		n = -n;
	}
	if (n > 9 && *count < MAX_LENGTH - 1)
		ft_putnbr(n / 10, count, res);
	c = (n % 10) + '0';
	res[*count] = c;
	(*count)++;
}

static void	ft_puthex(unsigned int n, int *count, char res[MAX_LENGTH])
{
	char	*hex;

	hex = "0123456789abcdef";
	if (n >= 16 && *count < MAX_LENGTH - 1)
		ft_puthex(n / 16, count, res);
	else
		return ;
	res[*count] = hex[n % 16];
	(*count)++;
}

static void	ft_handle_str(const char **str,
	va_list args, int *count, char res[MAX_LENGTH])
{
	if (**str == 's')
		ft_putstr(va_arg(args, char *), count, res);
	else if (**str == 'd')
		ft_putnbr(va_arg(args, int), count, res);
	else if (**str == 'x')
		ft_puthex(va_arg(args, unsigned int), count, res);
	else
	{
		res[*count] = *(*str);
		(*count)++;
	}
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		count;
	char	res[MAX_LENGTH];

	ft_bzero(res, MAX_LENGTH);
	count = 0;
	va_start(args, str);
	while (*str && count < MAX_LENGTH - 1)
	{
		if (*str == '%' && *(str + 1))
		{
			str++;
			ft_handle_str(&str, args, &count, res);
		}
		else
		{
			res[count++] = *str;
		}
		str++;
	}
	va_end(args);
	write(1, res, ft_strlen(res));
	return (count);
}
