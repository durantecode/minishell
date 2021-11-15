/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:01:32 by ldurante          #+#    #+#             */
/*   Updated: 2021/11/15 15:32:31 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

extern	char **environ;

typedef struct s_input
{
	int		path_unset;
	char	*user_input;
	char	**split_path;
	char	**split_input;
	char	*cmd_path;
	t_list	**env_list;
}	t_input;

int		main(void);
void	read_input(t_input *in);
char	*ft_getenv(const char *str, t_input *in);

void	builtins(t_input *in);
void	echo(t_input *in);
void	export(t_input *in);
void	unset(t_input *in);

void	exec_cmd(t_input *in);

void	catch_signal(int signal, siginfo_t *info, void *context);
char	**cut_arg(const char *s);
#endif