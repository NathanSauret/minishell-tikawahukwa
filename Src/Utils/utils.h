#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "ft_get_next_line/get_next_line.h"
# include "ft_printf/ft_printf.h"

void	ft_freetabstr(char **tab);
char	*ft_itoa(int ft_n);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_uitoa(unsigned int ft_n);

#endif