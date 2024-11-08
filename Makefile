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
		Src/Parsing/parsing.c \
		Src/Parsing/token.c \
		Src/Parsing/parsing_utils.c \
		Src/Parsing/token_utils.c \
		Src/Parsing/dolar.c \
		Src/Parsing/dolar_utils.c \
		Src/Exec/Pipex/exec_pipex.c	\
		Src/Exec/Pipex/exec_struct_utils.c	\
		Src/Exec/Pipex/exit_error_pipex.c	\
		Src/Exec/Pipex/free_pipex.c	\
		Src/Exec/Pipex/pipes_pipex.c	\
		Src/Exec/Pipex/pipex.c	\
		Src/Exec/Pipex/prepare_for_exec.c	\
		Src/Exec/Pipex/redirections.c	\
		Src/Exec/exec.c \
		Src/Exec/exec_jeremy.c \
		Src/debug_utils.c \
		Src/Built_in/ft_exit.c \
		Src/Built_in/ft_cd.c \
		Src/Built_in/ft_echo.c \
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
	valgrind --leak-check=full --suppressions=supp.supp ./minishell

.PHONY: all clean fclean re
