/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 20:08:50 by ldurante          #+#    #+#             */
/*   Updated: 2021/11/09 21:29:01 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

void	pwd(t_input *input)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
	(void)input;
}

void	env(t_input *input)
{
	int	i;

	i = 0;
	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
	(void)input;
}

void	expand_var(char *str)
{
	char	*var;

	var = getenv(str);
	if (var)
		printf("%s ", var);
}

void	echo(t_input *input)
{
	int	i;

	i = 0;
	if (input->split_input[1] == NULL)
		printf("\n");
	else if (!(ft_strncmp(input->split_input[1], "-n", 3)))
	{
		if (input->split_input[2] != NULL)
		{
			i = 1;
			while (input->split_input[++i])
			{
				if (input->split_input[i][0] == '$')
					expand_var(input->split_input[i] + 1);
				else
					printf("%s ", input->split_input[i]);
			}
		}
	}
	else
	{
		i = 0;
		while (input->split_input[++i])
		{
			if (input->split_input[i][0] == '$')
				expand_var(input->split_input[i] + 1);
			else
				printf("%s ", input->split_input[i]);
		}
		printf("\n");
	}
}

void	cd(t_input *input)
{
	char	*path;
	char	*aux;
	char	*totalpath;

	path = getenv("HOME");
	if (input->split_input[1] == NULL)
		chdir(path);
	else if (input->split_input[1][0] == '~')
	{
		if (input->split_input[1][1] == '\0')
			chdir(path);
		else
		{
			aux = input->split_input[1];
			aux++;
			totalpath = ft_strjoin(path, aux);
			free(input->split_input[1]);
			input->split_input[1] = ft_strdup(totalpath);
			cd(input);
			free(totalpath);
		}
	}
	else if (chdir(input->split_input[1]) != 0)
		printf("minishell: cd: %s: No such file or directory\n", 
			input->split_input[1]);
}

void	builtins(t_input *input)
{
	if (!(ft_strncmp(input->split_input[0], "pwd", 4)))
		pwd(input);
	else if (!(ft_strncmp(input->split_input[0], "env", 4)))
		env(input);
	else if (!(ft_strncmp(input->split_input[0], "cd", 3)))
		cd(input);
	else if (!(ft_strncmp(input->split_input[0], "echo", 5)))
		echo(input);
	else if (!(ft_strncmp(input->split_input[0], "exit", 5)))
	{
		printf("%s\n", "exit");
		free(input->user_input);
		free_matrix(input->split_input);
		free_matrix(input->split_path);
		exit(0);
	}
	else
		exec_cmd(input);
	free_matrix(input->split_input);
	free(input->user_input);
	// if (input->split_input[0] == "export")
	// if (input->split_input[0] == "unset")
}

void	exec_cmd(t_input *input)
{
	int		i;
	char	*aux;
	char	*path;
	pid_t	pid;
	i = -1;
	input->cmd_path = NULL;
	while (input->split_path[++i])
	{
		aux = ft_strjoin(input->split_path[i], "/");
		path = ft_strjoin(aux, input->split_input[0]);
		if ((access(path, F_OK)) == 0)
			input->cmd_path = ft_strdup(path);
		free(aux);
		free(path);
	}
	if (input->cmd_path)
	{
		pid = fork();
		if (pid == 0)
			execve(input->cmd_path, input->split_input, environ);
		waitpid(pid, NULL, 0);
		free(input->cmd_path);
	}
	else
		printf("minishell: %s: command not found\n", input->split_input[0]);
}
