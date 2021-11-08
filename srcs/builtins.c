/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 20:08:50 by ldurante          #+#    #+#             */
/*   Updated: 2021/11/08 21:09:27 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd(void)
{
	char *pwd;
	
	pwd = NULL;
	printf("%s\n", getcwd(pwd, 0));
	free(pwd);
}

void	env(void)
{
	while (environ)
	{
		printf("%s\n", *environ++);
	}
}

void	builtins(t_input *input)
{
	if (!(ft_strncmp(input->split_input[0], "pwd", 3)))
		pwd();
	if (!(ft_strncmp(input->split_input[0], "env", 3)))
		env();
	// if (input->split_input[0] == "cd")
	// if (input->split_input[0] == "echo")
	// if (input->split_input[0] == "export")
	// if (input->split_input[0] == "unset")
}

void	get_builtins(t_input *input)
{
	int i;
	char *aux;
	char *path;
	pid_t	pid;
	
	i = 0;
	while (input->split_path[i])
	{
		aux = ft_strjoin(input->split_path[i], "/");
		path = ft_strjoin(aux, input->split_input[0]);
		if ((access(path, F_OK)) == 0)
			input->cmd_path = ft_strdup(path);
		free(aux);
		free(path);
		i++;
	}
	pid = fork();
	if (pid == 0)
	{
		execve(input->cmd_path, input->split_input, environ);
	}
	waitpid(pid, NULL, 0);
}