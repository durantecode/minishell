/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 20:08:50 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/19 14:36:56 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_absolute(t_input *in)
{
	DIR	*dir;

	if ((access(in->split_in[0], F_OK)) == 0)
	{		
		dir = opendir(in->split_in[0]);
		if (dir)
		{
			error_msg(in, IS_DIR, 0, 0);
			closedir(dir);
		}
		else
		{
			if ((access(in->split_in[0], X_OK)) == 0)
				execve(in->split_in[0], in->split_in, in->dup_env);
			else
				error_msg(in, ERR_PERM, 0, 1);
		}
	}
	else
		error_msg(in, ERR_FILE, 0, 1);
}

int	is_builtin2(t_input *in)
{
	if (in->split_in[2])
	{
		if (!(ft_strncmp(in->split_in[2], "pwd", 4)))
			return (1);
		else if (!(ft_strncmp(in->split_in[2], "env", 4)))
			return (1);
		else if (!(ft_strncmp(in->split_in[2], "cd", 3)))
			return (1);
		else if (!(ft_strncmp(in->split_in[2], "echo", 5)))
			return (1);
		else if (!(ft_strncmp(in->split_in[2], "export", 7)))
			return (1);
		else if (!(ft_strncmp(in->split_in[2], "unset", 6)))
			return (1);
		else if (!(ft_strncmp(in->split_in[2], "exit", 5)))
			return (1);
	}
	return (0);
}

int	is_builtin(t_input *in)
{
	if (!(ft_strncmp(in->split_in[0], "pwd", 4)))
		return (1);
	else if (!(ft_strncmp(in->split_in[0], "env", 4)))
		return (1);
	else if (!(ft_strncmp(in->split_in[0], "cd", 3)))
		return (1);
	else if (!(ft_strncmp(in->split_in[0], "echo", 5)))
		return (1);
	else if (!(ft_strncmp(in->split_in[0], "export", 7)))
		return (1);
	else if (!(ft_strncmp(in->split_in[0], "unset", 6)))
		return (1);
	else if (!(ft_strncmp(in->split_in[0], "exit", 5)))
		return (1);
	return (0);
}

void	exec_args(t_input *in)
{
	if (!(ft_strncmp(in->split_in[0], "pwd", 4)))
		pwd(in);
	else if (!(ft_strncmp(in->split_in[0], "env", 4)))
		env(in, 0);
	else if (!(ft_strncmp(in->split_in[0], "cd", 3)))
		cd(in);
	else if (!(ft_strncmp(in->split_in[0], "echo", 5)))
		echo(in);
	else if (!(ft_strncmp(in->split_in[0], "export", 7)))
		export(in);
	else if (!(ft_strncmp(in->split_in[0], "unset", 6)))
		unset(in, 1);
	else if (!(ft_strncmp(in->split_in[0], "./minishell", 12)))
		exec_minishell(in);
	else if (!(ft_strncmp(in->split_in[0], "exit", 5)))
		my_exit(in);
	else if (!(ft_strchr(in->split_in[0], '/')))
		exec_cmd(in);
	else
		exec_absolute(in);
}
