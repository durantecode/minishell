/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 20:08:50 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/16 14:00:11 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(t_input *in)
{
	if (!(ft_strncmp(in->split_input[0], "pwd", 4)))
		return (1);
	else if (!(ft_strncmp(in->split_input[0], "env", 4)))
		return (1);
	else if (!(ft_strncmp(in->split_input[0], "cd", 3)))
		return (1);
	else if (!(ft_strncmp(in->split_input[0], "echo", 5)))
		return (1);
	else if (!(ft_strncmp(in->split_input[0], "export", 7)))
		return (1);
	else if (!(ft_strncmp(in->split_input[0], "unset", 6)))
		return (1);
	else if (!(ft_strncmp(in->split_input[0], "exit", 5)))
		return (1);
	else if (!(ft_strncmp(in->split_input[0], "./minishell", 12)))
		return (1);
	return (0);
}

void	exec_args(t_input *in)
{

	if (!(ft_strncmp(in->split_input[0], "pwd", 4)))
		pwd();
	else if (!(ft_strncmp(in->split_input[0], "env", 4)))
		env(in, 0);
	else if (!(ft_strncmp(in->split_input[0], "cd", 3)))
		cd(in);
	else if (!(ft_strncmp(in->split_input[0], "echo", 5)))
		echo(in);
	else if (!(ft_strncmp(in->split_input[0], "export", 7)))
		export(in);
	else if (!(ft_strncmp(in->split_input[0], "unset", 6)))
		unset(in, 1);
	else if (!(ft_strncmp(in->split_input[0], "./minishell", 12))
		&& in->total_pipes == 1)
		exec_minishell(in);
	else if (!(ft_strncmp(in->split_input[0], "exit", 5)))
		my_exit(in);
	else if (!(ft_strchr(in->split_input[0], '/')))
		exec_cmd(in);
	else
		exec_absolute(in);
}
