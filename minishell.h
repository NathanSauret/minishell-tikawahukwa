/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 23:10:03 by j_sk8             #+#    #+#             */
/*   Updated: 2024/11/05 16:37:01 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
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
# include <readline/readline.h>
# include <readline/history.h>

# define INPUT		1	//"<"
# define HEREDOC	2	//"<<"
# define TRUNC		3	//">"
# define APPEND		4	//">>"
# define PIPE		5	//"|"
# define CMD		6	//"command"
# define ARG		7	//"argument"

# define ERR_MALLOC	"malloc error\n"
# define ERR_PIPE	"pipe error\n"
# define ERR_FORK	"fork error\n"

# define MAX_PATH_LENGTH 256

typedef struct s_token
{
	char			*str;
	char			**command_line;
	char			*path;
	int				cmd_line_size;
	int				type;
	int				is_builtin;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct t_cmd
{
	int				is_builtin;
	char			**cmd;
	char			*path;
	t_token			*tokens;
	struct t_cmd	*next;
	struct t_cmd	*prev;

}	t_cmd;

typedef struct t_env
{
	char			*value;
	struct t_env	*next;
}	t_env;

typedef struct t_data
{
	char			*input;
	char			**args;
	int				num_of_pipe;
	t_env			*env;
	t_token			*token;
	t_cmd			*cmd;
	pid_t			pid;
}	t_data;

/*initialization*/
int		env_init(t_data *data, char **env_array);
char	*get_ex_path(char *cmd, t_data *data);
void	data_init(t_data *data);

/*utils*/
int		exit_error2(t_data *data, char *str);
void	free_env(t_env *env);
void	free_token(t_data *data);
int		is_error(char *str, t_data *data);

/*init*/
int		ft_cmd_lstadd_back(t_cmd **lst, t_cmd *new);
t_cmd	*ft_cmd_lstnew(char **cmd);
void	ft_cmd_lstclear(t_cmd **lst);
int		ft_token_lstadd_back(t_token **lst, t_token *new);
void	ft_token_lstclear(t_token **lst);
t_token	*ft_token_lstnew(char *str, int type);
t_token	*ft_token_lstlast(t_token *lst);
t_cmd	*ft_cmd_lstlast(t_cmd *lst);

/*parsing*/
int		parsing(t_data *data);
int		add_token(t_data *data);
int		get_arg(t_data *data, char **str);
char	**tokens_to_args(t_token *token_list);
int		line_is_empty(char *str);
int		fill_cmd_struct(t_data *data);

/*parsing utils*/
int		check_quote(char *str);
int		is_quote(char c);
int		line_is_empty(char *str);
int		is_cmd(t_token *token);
int		token_len(char *str, int *start, int *space, t_token *token);
int		get_type(t_token *token, char *str, int *type, int len);
int		is_operator(char *str);
int		get_sorted_arg(t_data *data);
int		token_parsing(t_data *data);

/*pipex*/
int		main_pipex(int argc, char *argv[], char *envp[]);

/*debug*/
void	print_token(t_token *token, int show_args);
void	print_3d(char **str);
void	print_cmd(t_cmd *cmd);
int		exec_test(char *str, t_data *data, char **env);

/*exec*/
int		exec(t_data *data, char **env);

/*builtins*/
int		ft_exit(t_data *data);
int		ft_cd(char **args);
int		ft_echo(char **arg);
#endif
