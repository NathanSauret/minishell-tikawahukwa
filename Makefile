NAME 	= minishell
CC		= cc
CFLAGS	= -Wall -Werror -Wextra -g3
LIBFT_DIR = libft
LIBFT = -L $(LIBFT_DIR) -lft

SRC =	Src/main.c	\
		Src/Initialization/init.c	\
		Src/Initialization/token_list.c \
		Src/Terminate/free.c \
		Src/Terminate/exit.c \
		Src/Utils/free_token.c \
		Src/Utils/signals.c \
		Src/Utils/array_utils.c \
		Src/Utils/utils.c \
		Src/Parsing/parsing.c \
		Src/Parsing/token.c \
		Src/Parsing/parsing_utils.c \
		Src/Parsing/token_utils.c \
		Src/Parsing/dolar.c \
		Src/Parsing/dolar_utils.c \
		Src/Exec/execute_commands.c	\
		Src/Exec/exec_struct_utils.c	\
		Src/Exec/exec.c	\
		Src/Exec/exit_error_exec.c	\
		Src/Exec/free_exec.c	\
		Src/Exec/here_doc.c	\
		Src/Exec/pipes_exec.c	\
		Src/Exec/prepare_for_exec.c	\
		Src/Exec/redirections.c	\
		Src/Exec/sleep_case.c	\
		Src/debug_utils.c \
		Src/Built_in/ft_exit.c \
		Src/Built_in/ft_cd.c \
		Src/Built_in/ft_pwd.c \
		Src/Built_in/ft_echo.c \
		Src/Built_in/ft_env.c \
		Src/Built_in/ft_export.c \
		Src/Built_in/ft_unset.c \
		Src/Initialization/cmd_list.c \
		Src/Parsing/cmd_struct_fill.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(CC) -o $(NAME) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline
	@clear
	@echo "Compilation done!"

clean:
	@$(MAKE) clean -C $(LIBFT_DIR)
	@rm -f $(OBJ)
	@clear
	@echo "Cleaning done!"

fclean:
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@rm -f $(OBJ)
	@rm -f $(NAME)
	@rm -rf
	@clear
	@echo "Full cleaning done!"

re: fclean all
	@clear
	@echo "Re:Zero - Re:Clean and compile again."

run:
	make
	valgrind --trace-children=yes --suppressions=supp.supp --quiet ./minishell

.PHONY: all clean fclean re
