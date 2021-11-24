/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:29:09 by ldurante          #+#    #+#             */
/*   Updated: 2021/11/24 18:53:11 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_cmd(t_input *in)
{
	int		i;
	char	*aux;
	char	*path;
	pid_t	pid;

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
			break;
		}
		free(aux);
		free(path);
	}
	if (in->cmd_path && in->path_unset == 0)
	{
		printf("%s\n", in->cmd_path);
		pid = fork();
		if (pid == 0)
			execve(in->cmd_path, in->split_input, environ);
		waitpid(pid, NULL, 0);
		free(in->cmd_path);
	}
	else
	{
		if (in->path_unset == 0)
			printf("minishell: %s: command not found\n", in->split_input[0]);
		else
			printf("minishell: %s: No such file or directory\n",
				in->split_input[0]);
	}
}
