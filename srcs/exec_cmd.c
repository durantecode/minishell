/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:29:09 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/09 18:55:24 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_absolute(t_input *in)
{
	DIR 	*dir;

	if ((access(in->split_input[0], F_OK)) == 0)
	{
		dir = opendir(in->split_input[0]);
		if (dir)
		{
			printf("minishell: %s: is a directory\n", in->split_input[0]);
			closedir(dir);
		}
		else
		{
			if ((access(in->split_input[0], X_OK)) == 0)
				execve(in->split_input[0], in->split_input, in->dup_env);
			else
				printf("minishell: %s: Permission denied\n", in->split_input[0]);
		}
	}
	else
		printf("minishell: %s: No such file or directory\n", in->split_input[0]);
	exit (0);
}

/* Revisar get_path con una función extra */

void	get_path(t_input *in)
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
}

void	exec_cmd(t_input *in)
{
	int		i;
	char	*aux;
	char	*path;

	get_path(in);
	i = -1;
	in->cmd_path = NULL;
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
	if (in->cmd_path && in->path_unset == 0)
	{
		// in->split_input[0] = NULL;
		// write(1, in->split_input[1], ft_strlen(in->split_input[1]));
		// print_matrix(in->dup_env);
		execve(in->cmd_path, in->split_input, in->dup_env);
		free(in->cmd_path);
	}
	else
	{
		if (in->path_unset == 0)
			error_msg(in, ERR_CMD, 1);
			// printf("minishell: %s: command not found\n", in->split_input[0]);
		else
			error_msg(in, ERR_FILE, 1);
			// printf("minishell: %s: No such file or directory\n",
			// 	in->split_input[0]);
	}
	// exit (0);
}
