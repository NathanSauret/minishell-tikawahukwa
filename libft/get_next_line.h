/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:05:43 by nsauret           #+#    #+#             */
/*   Updated: 2024/10/14 21:52:27 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include "libft.h"

char	*get_next_line(int fd, int status);
char	*free_and_line(char *buffer, char **stache, int sz, int status);
char	*_get_line(char *stache);
char	*new_line(char *stache);
char	*gnl_strjoin(char *s1, char *s2);

#endif
