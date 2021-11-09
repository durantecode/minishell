/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:01:32 by ldurante          #+#    #+#             */
/*   Updated: 2021/11/09 01:22:17 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/time.h>
# include <stdio.h>
# include <editline/readline.h>
# include <signal.h>

extern char **environ;

typedef struct s_input
{
	char	*user_input;
	char	**split_path;
	char	**split_input;
	char	*cmd_path;
	int		builtin_executed;
}	t_input;

int		main(void);
void	exec_cmd(t_input *input);
void	builtins(t_input *input);

#endif