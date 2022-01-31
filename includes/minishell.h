/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:01:32 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/31 19:38:07 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <errno.h>

# define R_END 0
# define W_END 1

# define SHELL "minishell: "
# define IS_DIR "is a directory"
# define ERR_PIPE "Pipe error"
# define ERR_FORK "Fork error"
# define ERR_DUP "Dup error"
# define ERR_SYNTAX "Syntax error near unexpected token `newLine"
# define ERR_SYNTAX_PIPE "Syntax error near unexpected token '|'"
# define ERR_SYNTAX_IN "Syntax error near unexpected token '<'"
# define ERR_SYNTAX_OUT "Syntax error near unexpected token '>'"
# define ERR_CMD "command not found"
# define ERR_FILE "No such file or directory"
# define ERR_PERM "Permission denied"
# define ERR_BIN "cannot execute binary file"
# define ERR_HOME "HOME not set"
# define ERR_ID "not a valid identifier"
# define ERR_ID2 "minishell: `': not a valid identifier"
# define ERR_ARG "Syntax error: unpaired quotes"
# define ERR_ARG2 "too many arguments"
# define ERR_SHLVL "warning: shell level too high, resetting to 1"
# define ERR_TOOLONG "File name too long"
# define ERR_HDOC "here_doc: could not find here_doc file"

extern int	g_exit_status;

typedef struct s_arg
{
	int		*quotes;
	char	**arg;
}	t_arg;

typedef struct s_flags
{
	int	i;
	int	j;
	int	start;
	int	count;
	int	count_double;
	int	single_q;
	int	double_q;
	int	global_q;
	int	global_count;
	int	global_sp;
}	t_flags;

typedef struct s_input
{
	int		fd[2][2];
	int		status;
	int		fd_in;
	int		fd_out;
	int		is_err;
	int		is_infile;
	int		is_outfile;
	int		is_hdoc;
	int		back_stdout;
	int		path_unset;
	int		total_pipes;
	int		q_state_size;
	int		*q_state;
	char	*prompt;
	char	*user_in;
	char	*cmd_path;
	char	**split_path;
	char	**split_in;
	char	**dup_env;
	t_list	**env_list;
	t_flags	f;
}	t_input;

int		main(int argc, char **argv, char **environ);
int		error_msg(t_input *in, char *MSG, int n, int is_abs);
void	free_list(t_input *in, t_list *arg_list);
int		char_sp(char c);
char	*ft_getenv(const char *str, t_input *in);

void	init_env_list(t_input *in, t_list **envp, char **environ);
void	init_flags(t_input *in);
void	init_arg_list(t_input *in);
void	update_env_var(t_input *in, char *var, char *value);
void	check_basic_vars(t_input *in);

void	read_input(t_input *in);
int		check_error_pipes(t_input *in);
void	split_args(t_input *in);
int		count_tokens(char *s, t_input *in, int split);
int		check_args(t_input *in);
void	expand_vars(t_input *in);
char	*get_expanded_var(char *str, int i);
void	insert_exp_var(t_input *in, char **var, char **aux, int j);
void	check_quotes(t_input *in);
int		count_pipes(t_input *in);
char	**quotes(t_input *in);
int		quotes_state(t_input *in, char *str);

int		is_builtin(t_input *in);
int		is_builtin2(t_input *in);
void	cd(t_input *in);
void	echo(t_input *in);
void	env(t_input *in, int type);
void	my_exit(t_input *in);
void	export(t_input *in);
void	pwd(t_input *in);
void	unset(t_input *in, int j);
void	exec_minishell(t_input *in);
void	exec_absolute(t_input *in);

void	exec_args(t_input *in);
void	exec_cmd(t_input *in);
void	pipex(t_input *in, t_list *arg_list);
void	if_minishell(t_input *in);
void	check_redirs(t_input *in);
int		check_hdoc(t_input *in);
void	exec_hdoc(t_input *in);
void	here_doc(t_input *in, int i);
void	remove_redir(t_input *in, int i);
void	unset_from_list(t_input *in, char **var, int size_var);

void	handler(int code);
void	handler2(int code);
void	handler3(int code);
void	handler4(int code);

#endif
