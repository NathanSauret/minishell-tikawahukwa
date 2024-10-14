# ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAX_ARGS 100
typedef struct t_env
{
	char	*value;
	struct t_env	*next;
} t_env;

typedef struct t_data
{
	struct t_env	*env;
	char *input;
	char *token;
	char *args[MAX_ARGS];
	pid_t pid;
} t_data;

int				env_init(t_data *data, char **env_array);
void			free_env(t_env *env);

#endif
