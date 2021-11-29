/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:03:38 by ldurante          #+#    #+#             */
/*   Updated: 2021/11/29 13:38:56 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	leaks(void)
{
	system("leaks -q minishell");
}

void	init_structs(t_input *in, t_list **envp)
{
	char	*aux;

	in->path_unset = 0;
	in->env_list = envp;
	aux = ft_getenv("PATH", in);
	in->split_path = ft_split(aux, ':');
	free(aux);
	if (!in->split_path)
	{
		in->path_unset = 1;
		in->split_path = ft_split(" . ", '.');
	}
	in->user_input = NULL;
	in->split_input = NULL;
	in->cmd_path = NULL;
}

void sigint_handler(int sig) 
{
	(void)sig;
	write(1, &"\n", 1);
    return;
}

int	main(void)
{
	t_input				in;
	t_list				*envp;
	//struct sigaction	sa;

	atexit(leaks);
	if (!(*environ))
	{
		environ = malloc(sizeof(char *) * 5);
		environ[0] = ft_strjoin("PWD=", getcwd(NULL, 0));
		environ[1] = ft_strdup("SHLVL=1");
		environ[2] = ft_strdup("_=/usr/bin/env");
		environ[3]
			= ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
		environ[4] = NULL;
	}
	envp = NULL;
	init_env_list(&envp);
	init_structs(&in, &envp);
	//sa.sa_sigaction = catch_signal;
	while (1)
	{
		//sigaction(SIGINT, &sa, NULL);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		read_input(&in);
		//signal(SIGQUIT, SIG_IGN);
	}
	return (0);
}
