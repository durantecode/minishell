/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 20:08:50 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/09 15:46:52 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd(t_input *in)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
	(void)in;
}

void	cd(t_input *in)
{
	char	*home_path;
	char	*aux;
	char	*full_path;

	home_path = ft_getenv("HOME", in);
	if (in->split_input[1] == NULL)
		chdir(home_path);
	else if (in->split_input[1][0] == '~')
	{
		if (in->split_input[1][1] == '\0')
			chdir(home_path);
		else
		{
			aux = in->split_input[1];
			aux++;
			full_path = ft_strjoin(home_path, aux);
			free(in->split_input[1]);
			in->split_input[1] = ft_strdup(full_path);
			cd(in);
			free(full_path);
		}
	}
	else if (chdir(in->split_input[1]) != 0)
		printf("minishell: cd: %s: No such file or directory\n",
			in->split_input[1]);
}

void	exec_minishell(t_input *in)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		execve(in->split_input[0], in->split_input, in->dup_env);
	}
	waitpid(pid, NULL, 0);
}

int		is_builtin(t_input *in)
{
	if (!(ft_strncmp(in->split_input[0], "pwd", 4)))
		return (1);
	else if (!(ft_strncmp(in->split_input[0], "env", 4)))
		return (1);
	else if (!(ft_strncmp(in->split_input[0], "cd", 3)))
		return (1);
	else if (!(ft_strncmp(in->split_input[0], "echo", 5)))
		return (1);
	else if (!(ft_strncmp(in->split_input[0], "export", 7)))
		return (1);
	else if (!(ft_strncmp(in->split_input[0], "unset", 6)))
		return (1);
	else if (!(ft_strncmp(in->split_input[0], "exit", 5)))
		return (1);
	else if (!(ft_strncmp(in->split_input[0], "./minishell", 12)))
		return (1);
	return (0);
}

void	builtins(t_input *in)
{
	if (!(ft_strncmp(in->split_input[0], "pwd", 4)))
		pwd(in);
	else if (!(ft_strncmp(in->split_input[0], "env", 4)))
		env(in);
	else if (!(ft_strncmp(in->split_input[0], "cd", 3)))
		cd(in);
	else if (!(ft_strncmp(in->split_input[0], "echo", 5)))
		echo(in);
	else if (!(ft_strncmp(in->split_input[0], "export", 7)))
		export(in);
	else if (!(ft_strncmp(in->split_input[0], "unset", 6)))
		unset(in);
	else if (!(ft_strncmp(in->split_input[0], "./minishell", 12)) && in->total_pipes == 1)
		exec_minishell(in);
	else if (!(ft_strncmp(in->split_input[0], "exit", 5)))
	{
		if (in->total_pipes == 1)
			printf("%s\n", "exit");
		exit(0);
	}
	else if (!(ft_strchr(in->split_input[0], '/')))
		exec_cmd(in);
	else
		exec_absolute(in);
	free(in->user_input);
}
