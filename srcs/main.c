/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:03:38 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/08 01:28:25 by ldurante         ###   ########.fr       */
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
	in->split_arg = NULL;
	in->cmd_path = NULL;
}

void sigint_handler(int sig) 
{
	(void)sig;
	write(1, &"\n", 1);
    return;
}

int	main(int argc, char **argv, char **environ)
{
	t_input				in;
	t_list				*envp;

	envp = NULL;
	init_env_list(&in, &envp, environ);
	init_structs(&in, &envp);
	if (argc == 1)
	{
		while (1)
		{
			//printf("holaa\n");
			read_input(&in);
		}
	}
	(void)argc;
	(void)argv;
	return (0);
}
