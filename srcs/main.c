/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:03:38 by ldurante          #+#    #+#             */
/*   Updated: 2021/11/08 18:48:07 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	leaks()
{
	system("leaks minishell");
}

void	get_builtin(char *cmd, char **split_path)
{
	int i;
	char *aux;
	char *path;
	char *cmd_path;		//Esta es temporal hasta que creemos la estructura
	
	i = 0;
	while (split_path[i])
	{
		aux = ft_strjoin(split_path[i], "/");
		path = ft_strjoin(aux, cmd);
		if ((access(path, F_OK)) == 0)
			cmd_path = ft_strdup(path);
		free(aux);
		free(path);
		i++;
	}
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		char* argv[] = { cmd, NULL };
  		char* envp[] = { "some", "environment", NULL };
		execve(cmd_path, argv, envp);
	}
	waitpid(pid, NULL, 0);
	// printf("%s\n", cmd_path);
}

void	to_read(char **split_path)
{
	char	*string;
	char	*prompt;

	prompt = ft_strjoin(getenv("USER"), "@minishell% ");
	string = readline(prompt);
	free(prompt);
	get_builtin(string, split_path);
}

int		main(int argc, char **argv, char **envp)
{
	char **split_path;

	//atexit(leaks);
	split_path = ft_split(getenv("PATH"), ':');
	while (1)
	{
		to_read(split_path);
	}
	(void)argc;
	(void)argv;
	return (0);
}