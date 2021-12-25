/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:01:32 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/25 17:25:09 by ldurante         ###   ########.fr       */
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
# define ERR_ARG "Syntax error near (INSERTAR QUOTES)"

extern int exit_status;

typedef struct s_arg
{
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
	int		fd_in;
	int		fd_out;
	int		path_unset;
	int		total_pipes;
	int		n_bytes;
	char	*prompt;
	char	*user_input;
	char	*cmd_path;
	char	**split_path;
	char	**split_input;
	char	**dup_env;
	char	**old_environ;
	t_list	**env_list;
	t_flags	flags;
}	t_input;

int		main(int argc, char **argv, char **environ);
int		error_msg(t_input *in, char *MSG, int n);

void	init_env_list(t_input *in, t_list **envp, char **environ);
void	init_flags(t_input *in);
void	init_arg_list(t_input *in);

void	read_input(t_input *in);
char	*split_pipes(t_input *in);
void	check_args(t_input *in);
void	check_redirs(t_input *in);

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

void	check_errors_aux(t_input *in);

void	exec_args(t_input *in);
void	exec_cmd(t_input *in);
void	exec_absolute(t_input *in);
void	here_doc(t_input *in, int i);

void	unset_aux(t_list *aux, char *var, int size_var);

int		count_pipes(t_input *in);

void	sig_handler(int signum);

#endif