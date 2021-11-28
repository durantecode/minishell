/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:01:32 by ldurante          #+#    #+#             */
/*   Updated: 2021/11/26 15:32:12 by ldurante         ###   ########.fr       */
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

extern char	**environ;

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
	t_list	**env_list;
	t_flags	flags;
}	t_input;

int		main(void);
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
void	init_env_list(t_list **envp);

void	exec_cmd(t_input *in);
void	exec_absolute(t_input *in);

void	catch_signal(int signal, siginfo_t *info, void *context);
#endif