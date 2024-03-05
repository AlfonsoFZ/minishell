/* ************************************************************************** */
/*                                                                        */
/*                                                    :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com    +#+  +:+       +#+        */
/*                                            +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:18:15 by alfofern          #+#    #+#             */
/*   Updated: 2024/01/22 11:35:49 by alfofern         ###   ########.fr       */
/*                                                                        */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include "errors.h"
# include <curses.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <signal.h>
# include <string.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <dirent.h>

# define PROMPT "minishell$ "
# define RED			"\x1b[31m"
# define PURPLE 		"\x1b[35m"
# define GREEN	 		"\x1b[32m"
# define YELLOW 		"\x1b[33m"
# define COLOR_RESET 	"\x1b[0m"

extern int	g_s_status;
typedef struct s_cmd
{
	char			*infile;
	char			*outfile;
	char			*grossname;
	int				ambiguous;
	int				orig_fd[2];
	int				fd_in;
	int				fd_out;
	int				in_heredoc;
	char			*del;
	int				deltype;
	char			*res;
	char			*next;
	char			*hdpath;
	int				out_append;
	char			*io_error_name;
	int				io_error;
	int				index;
	char			*argsstr;
	char			**args;
	struct s_data	*dt;
}	t_cmnd;

typedef struct s_env
{
	int				index;
	char			*var_name;
	char			*var_value;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	char	*user_input;
	char	*last_cmnd_arg;
	int		last_exit;
	char	*last_exit_str;
	int		n_pipes;
	int		**pipes;
	int		sq_counter;
	int		dq_counter;
	int		sq_active;
	int		dq_active;
	int		error;
	char	**cmds;
	char	**env;
	char	*path;
	int		ppid;
	char	*home;
	char	*pwd;
	pid_t	*n_pid;
	t_cmnd	**cmnd;
	t_env	*env_lst;
}	t_data;

/*charge_env_00.c*/
void	ft_charge_env_list(char **env_mtrx, t_env **env);
void	ft_add_env_list_node(char *env_str, t_env **env);
void	ft_init_new_node_values(t_env **new_node);
size_t	ft_new_node_var_name(char *env_str, t_env **new_node, char c);
void	ft_new_node_var_value(char *env_str, t_env **new_node);
/*charge_env_01.c*/
void	ft_charge_env_mtrx_from_envp(char **env, char ***env_mtrx);
void	ft_pull_values_over_mtrx(t_env **env_lst, char ***env_mtrx);
void	ft_charge_env_mtrx_from_lst(t_env **env_lst, char ***env_mtrx);
void	ft_index_env_lst(t_env **env_lst);
/*charge_env_02.c*/
void	ft_init_env_list_values(t_env **env);
void	ft_init_env_vars_index(t_env **env_lst);
int		ft_strcmp(char *s1, char *s2);
/*ft_mtrxlen.c*/
size_t	ft_mtrxlen(char **matrix);
/*ft_lstlen.c*/
int		ft_lstlen(t_env **env_lst);
/*(ft_isnumber.c)*/
size_t	ft_isnumber(char *str);
/*ft_clrscr.c*/
int		ft_clrscr(void);
/*free*/
void	ft_free_matrix(char **matrix);
void	ft_free_env_lst(t_env **vars);

/*builtins*/
int		ft_echo(t_cmnd *cmnd);
int		ft_env(t_data *dt, t_cmnd *cmnd);
int		ft_cd(t_data *dt, t_cmnd *cmnd);
void	ft_update_var(char *var_name, char *new_value, t_env **env);
int		ft_export(t_data *dt, t_cmnd *cmnd);
int		ft_unset(t_data *dt, t_cmnd *cmnd);
int		ft_pwd(t_data *dt, t_cmnd *cmnd);

/*print*/
void	ft_print_export(t_env *env_lst);
void	ft_print_minishell_title(void);

void	ft_print_env_list(t_env *env);
char	*get_var_value(t_cmnd *cmnd, char *name);
void	ft_update_env_var(char *str, t_env **env_lst);
int		ft_is_in_env_lst(char *str, t_env *env_lst);
int		ft_exit(t_data *dt, t_cmnd *cmnd);

char	*get_value(t_env **env, char *name);

/*signals*/
void	ft_ctrl_c(int sig);
void	ft_signals_proccess(int sig);
void	ft_ctrl_c_pipe(int sig);
void	ft_signal_heredoc(int sig);
int		ft_ctrl_d(t_data *dt, char *input);

/*initvar.c*/
bool	init_dt(t_data *dt, int i);
bool	first_init_dt(t_data *dt, char **env);
char	*read_prompt(t_data *dt);
int		parser(t_data *dt);
void	ft_split_free(char **res);
/*split_pipes.c*/
char	**ft_split_pipes(t_data *dt);
/*parser_utils.c*/
void	*ft_freenull(void *ptr);
int		ft_isspace(char c);
void	skipspace(char *cmd, int *i);
int		ft_check_nquotes(t_data *dt);
int		ft_check_quote(t_data *dt, char c);
void	check_quotes(int *squoted, int *dquoted, char c);
/*parser_utils2*/
int		set_error(t_data *dt, char *error);
void	set_io_error(t_cmnd *cmnd, char *str, int ernb);
char	*ft_free_join(char *s1, char *s2, int strtofree);
char	*ft_return_in_var(t_cmnd *cmnd, int *i, int sqdq[2], int ix);
/*parser_infile.c*/
void	checkinfile(t_cmnd *cmnd, char *cmd, int *i, int ix);
int		create_infile(t_cmnd *cmnd, char *cmd, int *i, int ix);
/*parser_outfile.c*/
void	checkoutfile(t_cmnd *cmnd, char *cmd, int *i, int ix);
int		create_outfile(t_cmnd *cmnd, int *i, int append, int ix);
/*parse_cmd*/
int		parse_cmd(t_data *dt, char **cmds);
/*ft_parser_quotes*/
char	*ft_quoted_str(char *cmd, char c, int *i);
/*ft_split_pipex.c*/
char	**ft_split_pipex(t_cmnd *cmnd);
/*main*/
int		is_builtin(t_data *dt, t_cmnd *cmnd, int i);
/*parser_var.c*/
char	*ft_get_var(t_cmnd *cmnd, int *i, int dq, int ix);
char	*check_special_var(t_cmnd *cmnd, char *s, int j, int dq);
char	*ft_get_var_hd(t_cmnd *cmnd, char *s, int *i, int dq);
/*executer.c*/
void	ft_execute(t_data *dt, char**args, int i, char **env);
char	*getpath(char *argv, char **env, int i, char *resok);
int		red_execute(t_data *dt);
/*checksyntax.c*/
int		check_syntax(t_data *dt, char **s, int i);
/*parser_heredoc.c*/
int		*ft_get_heredoc(t_cmnd *cmnd, char *cmd, int *i);
void	init_var(t_data *dt);
/*free.c*/
void	ft_free_cmnds(t_data *dt, int i);
void	ft_free_dt(t_data *dt);
void	final_free(t_data *dt);
/*parser_hd_delimeter.c*/
char	*ft_get_del(char *s, int *i, int squoted, int dquoted);
char	*set_delimiter(char *cmd, int *i, char *del, int *deltype);
/*redirections*/
int		ft_open_redir(t_data *dt, t_cmnd *cmnd);
int		ft_close_redir(t_cmnd *cmnd);
int		fill_redirect(t_data *dt, t_cmnd *cmnd, int i);
/*pipes*/
int		**ft_create_pipes(int n_pipes);
void	free_array(int **array, int n_pipes);
int		ft_create_pipe(t_data *dt, int i);
int		ft_get_next_pipe(char **s, t_data *dt);
/*red_utils*/
int		reset_stdin_stdout(t_cmnd *cmnd);
int		ft_check_io(t_data *dt, t_cmnd *cmnd);
/*free_matrix*/
void	ft_free_matrix(char **matrix);
void	ft_free_array(char **array);
void	ft_split_free(char **res);
/*executer_utils*/
int		ft_check_free(t_data *dt, char *str);
int		is_directory(char *path);
char	*get_last_arg(t_data *dt);
/*parser_inout_utils*/
char	*ft_getgrosname(t_cmnd *cmnd, int i, int ix);
int		is_last(t_cmnd *cmnd, int i, int ix);
char	*ft_returnvar(t_cmnd *cmnd, int *i, int sqdq[2], int ix);
int		check_directory(char *path);
int		isdir(t_cmnd *cmnd, char *outfile);
/*ft_sp_px_utils*/
void	eval_quotes(int *in_quotes, char str, char *quote);
int		ft_strcounter(char *str, int counter, int in_word, int in_quotes);
/*cd_utils*/
int		check_dir_permiss(char *npath);
char	*get_pwd(t_data *dt);
char	*change_pwd(t_data *dt, char *npath);
void	check_dir(const char *dir_path);
void	ft_update_var(char *var_name, char *new_value, t_env **env);

#endif