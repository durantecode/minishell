/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:01:32 by ldurante          #+#    #+#             */
/*   Updated: 2021/11/29 20:02:28 by ldurante         ###   ########.fr       */
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
# include <sys/wait.h>
# include <dirent.h>

// extern char	**environ;

# define R_END 0
# define W_END 1

typedef struct s_arg
{
	char	**arg;
	int		pipe_fd[2];
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
	char	*user_input;
	char	**split_path;
	char	**split_input;
	char	*cmd_path;
	char	**dup_env;
	t_list	**env_list;
	t_flags	flags;
}	t_input;

int		main(int argc, char **argv, char **environ);
void	init_flags(t_input *in);

void	read_input(t_input *in);
char	*split_pipes(t_input *in);
void	check_args(t_input *in);
int		count_tokens(const char *s, t_input *in, int split);
char	**quotes(t_input *in);
int		quotes_aux(t_input *in, char *str);
void	expand_vars(t_input *in);
char	*ft_getenv(const char *str, t_input *in);

void	builtins(t_input *in);
void	env(t_input *in);
void	echo(t_input *in);
void	export(t_input *in);
void	unset(t_input *in);
void	init_env_list(t_input *in, t_list **envp, char **environ);

void	exec_cmd(t_input *in);
void	pipes(t_input *in);
void	exec_absolute(t_input *in);

void	catch_signal(int signal, siginfo_t *info, void *context);
#endif