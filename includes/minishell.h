/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:01:32 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/09 19:21:05 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/ioctl.h>

# define R_END 0
# define W_END 1

# define SHELL "minishell"
# define ERR_PIPE "Pipe error\n"
# define ERR_FORK "Fork error\n"
# define ERR_DUP "Dup error\n"
# define ERR_SYNTAX "syntax error near \n"

# define ERR_CMD "command not found\n"
# define ERR_FILE "No such file or directory\n"
# define ERR_PERM "Permission denied\n"
# define ERR_BIN "cannot execute binary file\n"

# define ERR_ID "not a valid identifier\n"
# define ERR_ARG "Invalid argument\n"

typedef struct s_arg
{
	char	**arg;
	// int		pipe_fd[2];
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
	int		path_unset;
	int		total_pipes;
	int		n_bytes;
	char	*user_input;
	char	**split_path;
	char	**split_input;
	char	*cmd_path;
	char	**dup_env;
	t_list	**env_list;
	t_flags	flags;
}	t_input;

int		main(int argc, char **argv, char **environ);
int		error_msg(t_input *in, char *ERR, int n);

void	init_env_list(t_input *in, t_list **envp, char **environ);
void	init_flags(t_input *in);
void	init_arg_list(t_input *in);

void	read_input(t_input *in);
char	*split_pipes(t_input *in);
void	check_args(t_input *in);
int		count_tokens(const char *s, t_input *in, int split);
char	**quotes(t_input *in);
int		quotes_aux(t_input *in, char *str);
void	expand_vars(t_input *in);
char	*ft_getenv(const char *str, t_input *in);

int		is_builtin(t_input *in); 
void	builtins(t_input *in);
void	env(t_input *in);
void	echo(t_input *in);
void	export(t_input *in);
void	unset(t_input *in);

int		count_pipes(t_input *in);
void	list_to_matrix(t_input *in);
void	exec_cmd(t_input *in);
void	exec_absolute(t_input *in);

void	catch_signal(int signal, siginfo_t *info, void *context);
void	single_input(t_input *in, char **str);

#endif