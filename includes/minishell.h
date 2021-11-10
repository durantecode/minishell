/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:01:32 by ldurante          #+#    #+#             */
/*   Updated: 2021/11/10 12:56:21 by ldurante         ###   ########.fr       */
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

extern char **environ;

typedef struct s_input
{
	char	*user_input;
	char	**split_path;
	char	**split_input;
	char	*cmd_path;
}	t_input;

int		main(void);
void	read_input(t_input *in);
void	builtins(t_input *in);
void	echo(t_input *in);
void	exec_cmd(t_input *in);
void	catch_signal(int signal, siginfo_t *info, void *context);

#endif