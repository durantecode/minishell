/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:29:09 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/31 19:35:33 by ldurante         ###   ########.fr       */
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
		path = ft_strjoin(aux, in->split_in[0]);
		if ((access(path, F_OK)) == 0 && !ft_strncmp(path, "/", 1))
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
	char	**new_env;
	int		size;
	int		i;

	if (in->total_pipes)
		exit (0);
	size = 0;
	i = -1;
	while (in->dup_env[++i])
	{
		if (ft_strchr(in->dup_env[i], '='))
			size++;
	}
	new_env = dup_new_env(in->dup_env, size);
	if (execve(in->split_in[0], in->split_in, new_env) == -1)
		error_msg(in, ERR_CMD, 0, 0);
	free_matrix(new_env);
}

void	exec_cmd(t_input *in)
{
	get_path(in);
	in->cmd_path = NULL;
	if (get_cmd_path(in))
		execve(in->cmd_path, in->split_in, in->dup_env);
	else
	{
		if (in->path_unset == 0)
			error_msg(in, ERR_CMD, 0, 0);
		else
			error_msg(in, ERR_FILE, 0, 0);
	}
}
