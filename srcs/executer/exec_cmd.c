/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:29:09 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/14 21:58:51 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_path(t_input *in)
{
	char	*aux;

	in->path_unset = 0;
	aux = ft_getenv("PATH", in);
	in->split_path = ft_split(aux, ':');
	free(aux);
	if (!in->split_path)
	{
		in->path_unset = 1;
		in->split_path = ft_split(" . ", '.');
	}
	return (in->path_unset);
}

void	get_cmd_path(t_input *in)
{
	int		i;
	char	*aux;
	char	*path;

	i = -1;
	while (in->split_path[++i])
	{
		aux = ft_strjoin(in->split_path[i], "/");
		path = ft_strjoin(aux, in->split_input[0]);
		if ((access(path, F_OK)) == 0)
		{
			in->cmd_path = ft_strdup(path);
			free(aux);
			free(path);
			break ;
		}
		free(aux);
		free(path);
	}
}

void	exec_minishell(t_input *in)
{
	pid_t	pid;

	pid = fork();
	//print_matrix(in->dup_env);
	if (pid < 0)
		error_msg(in, ERR_FORK, 2);
	if (pid == 0)
		execve(in->split_input[0], in->split_input, in->dup_env);
	waitpid(pid, NULL, 0);
}

void	exec_absolute(t_input *in)
{
	DIR	*dir;

	if ((access(in->split_input[0], F_OK)) == 0)
	{
		dir = opendir(in->split_input[0]);
		if (dir)
		{
			error_msg(in, IS_DIR, 0);
			closedir(dir);
		}
		else
		{
			if ((access(in->split_input[0], X_OK)) == 0)
				execve(in->split_input[0], in->split_input, in->old_environ);
			else
				error_msg(in, ERR_PERM, 0);
		}
	}
	else
		error_msg(in, ERR_FILE, 0);
}

void	exec_cmd(t_input *in)
{
	get_path(in);
	in->cmd_path = NULL;
	get_cmd_path(in);
	if (in->cmd_path && in->path_unset == 0)
		execve(in->cmd_path, in->split_input, in->dup_env);
	else
	{
		if (in->path_unset == 0)
			error_msg(in, ERR_CMD, 0);
		else
			error_msg(in, ERR_FILE, 0);
	}
}
