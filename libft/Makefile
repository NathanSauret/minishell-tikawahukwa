# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmiccio <jmiccio <marvin@42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/15 13:45:19 by jmiccio           #+#    #+#              #
#    Updated: 2024/12/11 11:50:37 by jmiccio          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_is/ft_isalnum.c \
      ft_is/ft_isalpha.c \
      ft_is/ft_isascii.c \
      ft_is/ft_isdigit.c \
      ft_is/ft_isprint.c \
       ft_is/ft_is_space.c \
      ft_put/ft_putchar_fd.c \
      ft_put/ft_putendl_fd.c \
      ft_put/ft_putnbr_fd.c \
      ft_put/ft_putstr_fd.c \
      ft_str/ft_strchr.c \
      ft_str/ft_strdup.c \
      ft_str/ft_strjoin.c \
      ft_str/ft_strlcat.c \
      ft_str/ft_strlcpy.c \
      ft_str/ft_strlen.c \
      ft_str/ft_strmapi.c \
      ft_str/ft_strncmp.c \
      ft_str/ft_strstr.c \
      ft_str/ft_strnstr.c \
      ft_str/ft_strrchr.c \
      ft_str/ft_strtrim.c \
      ft_str/ft_substr.c \
      ft_other/ft_tolower.c \
      ft_other/ft_toupper.c \
      ft_other/ft_calloc.c \
      ft_other/ft_atoi.c \
      ft_other/ft_bzero.c \
      ft_other/ft_itoa.c \
      ft_other/ft_uitoa.c \
      ft_other/ft_memchr.c \
      ft_other/ft_memcmp.c \
      ft_other/ft_memcpy.c \
      ft_other/ft_memmove.c \
      ft_other/ft_memset.c \
      ft_other/ft_split.c \
      ft_lst/ft_lstnew.c \
      ft_lst/ft_lstadd_front.c \
      ft_lst/ft_lstsize.c \
      ft_lst/ft_lstlast.c \
      ft_lst/ft_lstadd_back.c \
      ft_lst/ft_lstdelone.c \
      ft_lst/ft_lstclear.c \
      ft_lst/ft_lstiter.c \
      ft_lst/ft_lstmap.c \
      ft_get_next_line/ft_get_next_line.c \
      ft_get_next_line/ft_get_next_line_utils.c \
      ft_printf/ft_printf.c   \
      ft_printerr/ft_printerr.c

OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -g3 -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
