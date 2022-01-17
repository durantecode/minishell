 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:01:32 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/14 12:47:56 by ldurante         ###   ########.fr       */
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

# define R_END 0
# define W_END 1

# define SHELL "minishell: "
# define IS_DIR "is a directory"
# define ERR_PIPE "Pipe error"
# define ERR_FORK "Fork error"
# define ERR_DUP "Dup error"
# define ERR_SYNTAX "syntax error near unexpected token"

# define ERR_CMD "command not found"
# define ERR_FILE "No such file or directory"
# define ERR_PERM "Permission denied"
# define ERR_BIN "cannot execute binary file"
# define ERR_HOME "HOME not set"

# define ERR_ID "not a valid identifier"
# define ERR_ID2 "minishell: `': not a valid identifier"
# define ERR_ARG "Syntax error near argument"
# define ERR_ARG2 "too many arguments"
# define ERR_SHLVL "warning: shell level too high, resetting to 1"

extern int g_exit_status;

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
	int		fd_error;
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
	char	*prompt;
	char	*user_input;
	char	*cmd_path;
	char	**split_path;
	char	**split_input;
	int		*quote_state;
	char	**dup_env;
	t_list	**env_list;
	t_flags	flags;
}	t_input;

int		main(int argc, char **argv, char **environ);
int		error_msg(t_input *in, char *MSG, int n, int is_abs);
int		char_space(char c);

void	init_env_list(t_input *in, t_list **envp, char **environ);
void	init_flags(t_input *in);
void	init_arg_list(t_input *in);
void	update_env_var(t_input *in, char *var, char *value);
void	check_basic_vars(t_input *in);

void	read_input(t_input *in);
void	split_pipes(t_input *in);
int		check_args(t_input *in);
void	check_redirs(t_input *in);
void	remove_redir(t_input *in, int i);

int		count_tokens(char *s, t_input *in, int split);
char	**quotes(t_input *in);
int		quotes_state(t_input *in, char *str);
void	expand_vars(t_input *in);
char	*ft_getenv(const char *str, t_input *in);

int		is_builtin(t_input *in);
void	cd(t_input *in);
void	echo(t_input *in);
void	env(t_input *in, int type);
void	my_exit(t_input *in);
void	export(t_input *in);
void	pwd(void);
void	unset(t_input *in, int j);
void	exec_minishell(t_input *in);

void	check_quotes(t_input *in);

void	exec_args(t_input *in);
void	exec_cmd(t_input *in);
void	exec_absolute(t_input *in);
void	here_doc(t_input *in, int i);
void	check_hdoc(t_input *in);
void	exec_hdoc(t_input *in);

void	unset_aux(t_input *in, char *var, int size_var);

int		count_pipes(t_input *in);

void	handler(int	code);
void	handler2(int code);
void	handler3(int code);
void	handler4(int code);



#endif

/*
	TO DO:

	Leaks
	Norma
*/ 