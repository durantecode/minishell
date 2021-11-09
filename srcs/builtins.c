/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 20:08:50 by ldurante          #+#    #+#             */
/*   Updated: 2021/11/09 16:16:00 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd(t_input *input)
{
	char *pwd;
	
	pwd = NULL;
	printf("%s\n", getcwd(pwd, 0));
	// input->builtin_executed = 1;
	free(pwd);
	(void)input;
}

void	env(t_input *input)
{
	int i;

	i = 0;
	while (environ[i] != '\0')
	{
		printf("%s\n", environ[i]);
		i++;
	}
	(void)input;
	// input->builtin_executed = 1;
}

void	cd(t_input *input)
{
	chdir(input->split_input[1]);
	// input->builtin_executed = 1;
}

void	builtins(t_input *input)
{
	if (!(ft_strncmp(input->split_input[0], "pwd", 3)))
		pwd(input);
	else if (!(ft_strncmp(input->split_input[0], "env", 3)))
		env(input);
	else if (!(ft_strncmp(input->split_input[0], "cd", 2)))
		cd(input);
	else if (!(ft_strncmp(input->split_input[0], "exit", 4)))
	{
		printf("%s\n", "exit");
		exit(0);
	}
	else
		exec_cmd(input);
	// if (input->split_input[0] == "echo")
	// if (input->split_input[0] == "export")
	// if (input->split_input[0] == "unset")
}

void	exec_cmd(t_input *input)
{
	int i;
	char *aux;
	char *path;
	pid_t	pid;
	
	i = 0;
	input->cmd_path = NULL;
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
	if (input->cmd_path)
	{	
		pid = fork();
		if (pid == 0)
		{
			execve(input->cmd_path, input->split_input, environ);
		}
		waitpid(pid, NULL, 0);
	}
	else
		printf("Error\n");
}