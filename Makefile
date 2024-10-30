NAME 	= minishell
CC		= cc
CFLAGS	= -Wall -Werror -Wextra -g3
LIBFT_DIR = libft
LIBFT = -L $(LIBFT_DIR) -lft

SRC =	Src/Pipex/check_args.c	\
		Src/Pipex/exit_error.c	\
		Src/Pipex/free.c	\
		Src/Pipex/get_files.c	\
		Src/Pipex/get_path.c	\
		Src/Pipex/here_doc.c	\
		Src/Pipex/ft_freetabstr.c \
		Src/Pipex/main.c	\
		Src/Pipex/pipes_utils.c	\
		Src/Pipex/pipex.c	\
		Src/main.c	\
		Src/Initialization/init.c	\
		Src/Initialization/token_list.c \
		Src/Terminate/free.c \
		Src/Terminate/exit.c \
		Src/Utils/free_token.c \
		Src/Parsing/parsing.c \
		Src/Parsing/token.c \
		Src/Parsing/parsing_utils.c \
		Src/Parsing/token_utils.c \
		Src/Exec/exec.c \
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
	valgrind --track-fds=yes --suppressions=supp.supp ./minishell

.PHONY: all clean fclean re
