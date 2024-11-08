/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsauret <nsauret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:00:45 by nsauret           #+#    #+#             */
/*   Updated: 2024/10/29 16:04:54 by nsauret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

int	ft_print_int(int el);
int	ft_print_char(int el);
int	ft_print_str(const char *el);
int	ft_print_strstr(char **el);
int	ft_print_pointer(unsigned long el);
int	ft_printf(const char *text, ...);
int	ft_print_unsigned(unsigned int el);
int	ft_print_hex(char type_of_hex, unsigned int el);

#endif
