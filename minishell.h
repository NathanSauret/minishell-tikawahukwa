/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:02:03 by j_sk8             #+#    #+#             */
/*   Updated: 2025/01/07 00:04:28 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define RESET        "\033[0m"
# define BLUE         "\033[34m"
# define BOLD_BLUE     "\033[1;34m"
# define BOLD_GREEN   "\033[1;32m"
# define BOLD_RED     "\033[1;31m"

# define INPUT		1	//"<"
# define HEREDOC	2	//"<<"
# define TRUNC		3	//">"
# define APPEND		4	//">>"
# define PIPE		5	//"|"
# define CMD		6	//"command"
# define ARG		7	//"argument"

# define ERR_MALLOC	"~ Tikawahukwa: malloc error\n"
# define ERR_PIPE	"~ Tikawahukwa: pipe error\n"
# define ERR_FORK	"~ Tikawahukwa: fork error\n"

extern int	g_signal;

typedef struct s_exec
{
	int				in;
	int				out;
	int				is_infile;
	int				is_outfile;
	int				is_builtin;
	char			**cmd;
	char			*path;
	struct s_exec	*next;
}	t_exec;

typedef struct s_pipex
{
	int		cmd_nb;
	int		*pipe;
	int		idx;
	t_exec	*exec;
}	t_pipex;

typedef struct s_token
{
	char			*str;
	char			**command_line;
	int				cmd_line_size;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct t_cmd
{
	char			**cmd;
	t_token			*tokens;
	struct t_cmd	*next;
	struct t_cmd	*prev;

}	t_cmd;

typedef struct t_env
{
	char			*value;
	struct t_env	*next;
	struct t_env	*prev;
}	t_env;

typedef struct t_data
{
	char			*input;
	int				num_of_pipe;
	int				exit_status;
	int				is_nl;
	int				env_len;
	char			**env_array;
	pid_t			pid;
	t_env			*env;
	t_cmd			*cmd;
	t_token			*token;
	t_pipex			*pipex;
}	t_data;

/*initialization*/
void	data_init(t_data *data);
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
int		ft_env_lstadd_back(t_env **lst, t_env *new);
void	ft_env_lstclear(t_env **lst);
t_env	*ft_env_lstnew(char *value);

/*emv_init*/
int		env_init(t_data *data, char **env_array);
int		shlvl_handler(t_data *data);

/*utils*/
void	prompt(t_data *data);
int		is_error(char *str, t_data *data, int exit_status);
void	signals(void);
void	handle_sigint(int sig);
void	here_doc_handler(int sig);
void	sort_array(char **arr, int len);
char	**lst_to_arr(t_data *data, t_env *env, int len);
int		ft_intlen(int n);
char	*ft_getenv(t_env *env, char *str);

/*parsing*/
int		parsing(t_data *data);
int		get_arg(t_data *data, char **str);
int		line_is_empty(char *str);
int		fill_cmd_struct(t_data *data);
int		check_valid_cmd(t_data *data, t_exec *exec);

/*parsing utils*/
int		check_quote(t_data *data, char *str);
int		is_quote(char c);
int		line_is_empty(char *str);
int		is_cmd(t_token *token);
int		is_operator(char *str);
int		is_operator2(int type, int pipe);
int		get_quote_state(char c, int quote);

/*token*/
int		add_token(t_data *data);
int		token_len(char *str, int *space, t_token *token);
int		get_type(t_token *token, char *str, int *type, int len);
int		token_parsing(t_data *data);

/*dolar utils*/
char	*handle_dolar(t_data *data, char *str, int *len);
int		copy_str(char **res, char **str, int *i, int len);
int		copy_var(char **res, char *var, int *i, int len);
char	**fill_var_name(char *str, int v_num, int v_pos[100], int v_len[100]);
int		full_len(t_data *data, char *token, char **var);
int		var_len(char *str, int *y);

/*free*/
void	terminate(t_data *data, char *msg, int ext_status);
void	free_env(t_env *env);
void	free_token(t_data *data);
void	free_array(char **arr);
char	**free_var(char **str, int len);
void	free_command_line(t_token *token);

/*debug*/
void	print_token(t_token *token);
void	print_tab(char **tab);
void	print_cmd(t_cmd *cmd);

/*     exec     */
// execute_commands.c
void	execute_commands(t_data *data, t_pipex *pipex);
// exec_struct_utils.c
t_exec	*execnew(t_cmd *cmd, int in, int out);
int		execadd_back(t_exec **exec, t_exec *new);
void	ft_exec_lstclear(t_exec **lst);
void	close_iofiles_and_free_prev_exec(t_pipex *pipex);
// exec.c
void	exec(t_data *data);
// free_exec.c
void	free_parent(t_pipex *pipex, t_data *data);
void	free_child(t_data *data, t_pipex *pipex);
// here_doc.c
int		here_doc(t_data *data, char *argv);
// pipes_exec.c
void	create_pipes(t_pipex *pipex, t_data *data);
void	close_pipes(t_pipex *pipex, t_data *data);
// prepare_for_exec.c
void	prepare_for_exec(t_data *data, t_pipex *pipex);
// redirections.c
int		redirection_input(t_data *data, t_pipex *pipex, t_cmd *cmd);
int		redirection_trunc(t_data *data, t_pipex *pipex, t_cmd *cmd);
int		redirection_append(t_data *data, t_pipex *pipex, t_cmd *cmd);

/*builtins*/
void	ft_exit(t_data *data, char **cmd);
int		ft_cd(t_data *data, t_env *env, char **args);
int		ft_echo(char **arg);
int		ft_pwd(void);
int		ft_echo(char **arg);
int		ft_env(t_env *env);
int		ft_export(char **str, t_data *data);
int		ft_unset(char **arg, t_data *data);

#endif
