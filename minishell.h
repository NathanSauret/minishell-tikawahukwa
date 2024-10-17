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

# define INPUT		1	//"<"
# define HEREDOC	2	//"<<"
# define TRUNC		3	//">"
# define APPEND		4	//">>"
# define PIPE		5	//"|"
# define CMD		6	//"|"
# define ARG		7	//"|"


# define ERR_MALLOC	"malloc error\n"
# define ERR_PIPE	"pipe error\n"
# define ERR_FORK	"fork error\n"

#define MAX_ARGS 100

typedef struct t_env
{
	char	*value;
	struct t_env	*next;
} t_env;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
} t_token;

typedef struct t_data
{
	char			*input;
	char			*tok;
	char			*args[MAX_ARGS];
	char			**arg;
	t_env	*env;
	t_token	*token;
	pid_t			pid;
} t_data;

/*initialization*/
int		env_init(t_data *data, char **env_array);
char	*get_ex_path(char *cmd, t_data *data);

/*utils*/
int		exit_error2(t_data *data, char *str);
void	free_env(t_env *env);
int		ft_token_lstadd_back(t_token **lst, t_token *new);
t_token	*ft_token_lstnew(char *str, int type);
void	ft_token_lstclear(t_token **lst);
void	free_token(t_data *data);

/*pipex*/
int		main_pipex(int argc, char *argv[], char *envp[]);

#endif
