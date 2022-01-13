/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:29:09 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/13 00:18:00 by ldurante         ###   ########.fr       */
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

int	get_cmd_path(t_input *in)
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
			return (1);
		}
		free(aux);
		free(path);
	}
	return (0);
}

char	**dup_new_env(char **matrix, int size)
{
	char	**out;
	int		i;
	int		j;

	i = 0;
	out = malloc(sizeof(char *) * (size + 1));
	if (!out)
		return (NULL);
	i = 0;
	j = 0;
	while (matrix[i])
	{
		if (ft_strchr(matrix[i], '='))
		{
			out[j] = ft_strdup(matrix[i]);
			j++;
		}
		i++;
	}
	out[j] = NULL;
	return (out);
}

void	exec_minishell(t_input *in)
{
	pid_t	pid;
	char	**new_env;
	int		size;
	int		i;

	size = 0;
	i = -1;
	while (in->dup_env[++i])
	{
		if (ft_strchr(in->dup_env[i], '='))
			size++;
	}
	new_env = dup_new_env(in->dup_env, size);
	pid = fork();
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (pid < 0)
		error_msg(in, ERR_FORK, -1);
	if (pid == 0)
	{
		if (execve(in->split_input[0], in->split_input, new_env) == -1)
			error_msg(in, ERR_CMD, 0);
	}
	waitpid(pid, NULL, 0);
	free_matrix(new_env);
}

void	exec_absolute(t_input *in)
{
	DIR	*dir;

	if ((access(in->split_input[0], F_OK)) == 0)
	{		
		dir = opendir(in->split_input[0]);
		if (dir)
		{
			error_msg(in, IS_DIR, 999);
			closedir(dir);
		}
		else
		{
			if ((access(in->split_input[0], X_OK)) == 0)
				execve(in->split_input[0], in->split_input, in->dup_env);
			else
				error_msg(in, ERR_PERM, 999);
		}
	}
	else
		error_msg(in, ERR_FILE, 999);
}

void	exec_cmd(t_input *in)
{
	get_path(in);
	in->cmd_path = NULL;
	if (get_cmd_path(in))
		execve(in->cmd_path, in->split_input, in->dup_env);
	else
	{
		if (in->path_unset == 0)
			error_msg(in, ERR_CMD, 0);
		else
			error_msg(in, ERR_FILE, 0);
	}
}
