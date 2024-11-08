/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid Date        by              +#+  #+#    #+#             */
/*   Updated: 2024/11/08 14:18:23 by jmiccio          ###   ########.fr       */
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

typedef struct s_exec
{
	int				in;
	int				out;
	int				is_builtin;
	char			**cmd;
	char			*path;
	struct s_exec	*next;
}	t_exec;

typedef struct s_pipex
{
	int		*here_doc;
	int		cmd_nb;
	int		*pipe;
	int		idx;
	pid_t	pid;
	t_exec	*exec;
}	t_pipex;

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
	t_cmd			*cmd;
	t_token			*token;
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
void	free_command_line(t_token *token);

/*init*/
int		ft_cmd_lstadd_back(t_cmd **lst, t_cmd *new);
t_cmd	*ft_cmd_lstnew(char **cmd);
void	ft_cmd_lstclear(t_cmd **lst);
int		ft_token_lstadd_back(t_token **lst, t_token *new);
void	ft_token_lstclear(t_token **lst);
void	ft_token_lstclear(t_token **lst);
t_token	*ft_token_lstnew(char *str, int type);
t_token	*ft_token_lstlast(t_token *lst);
t_cmd	*ft_cmd_lstlast(t_cmd *lst);
t_cmd	*ft_cmd_lstlast(t_cmd *lst);

/*parsing*/
int		parsing(t_data *data);
int		add_token(t_data *data);
int		get_arg(t_data *data, char **str);
char	**tokens_to_args(t_token *token_list);
int		line_is_empty(char *str);
int		fill_cmd_struct(t_data *data);
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
int		handle_dolar(t_data *data);
int		copy_str(char **res, char **str, int *i, int len);
int		copy_var(char **res, char *var, int *i, int len);
char	**free_var(char **str, int len);
char	**fill_var_name(char *str, int v_num, int v_pos[100], int v_len[100]);
int		full_len(t_token *token, char **var);

/*debug*/
void	print_token(t_token *token, int show_args);
void	print_3d(char **str);
void	print_cmd(t_cmd *cmd);
int		exec_test(char *str, t_data *data, char **env);
void	print_cmd(t_cmd *cmd);
int		exec_test(char *str, t_data *data, char **env);

/*     exec     */
// exec_pipex.c
void	exec_pipex(t_data *data, t_pipex *pipex, char **env);
// exec_struct_utils.c
t_exec	*execnew(t_cmd *cmd, int in, int out);
void	execadd_back(t_exec **exec, t_exec *new);
// exit_error_pipex.c
int		exit_error_pipex(t_pipex *pipex, int error_case, char *arg);
// free-pipex.c
void	parent_free(t_pipex *pipex, t_data *data);
void	child_free(t_pipex *pipex);
// pipes_pipex.c
int		create_pipes(t_pipex *pipex, t_data *data);
int		pipe_free(t_pipex *pipex);
void	close_pipes(t_pipex *pipex, t_data *data);
// pipex.c
int		pipex(t_data *data, char **env);
// prepare_for_exec.c
void	prepare_for_exec(t_data *data, t_pipex *pipex);
// redirections.c
int		redirection_input(t_cmd *cmd);
int		redirection_trunc(t_pipex *pipex, t_cmd *cmd);
// exec.c
int		exec(t_data *data, char **env);
int		exec2(t_data *data, char **env);

/*builtins*/
int		ft_exit(t_data *data);
int		ft_cd(char **args);
int		ft_echo(char **arg);
int		ft_cd(char **args);
int		ft_echo(char **arg);
#endif
