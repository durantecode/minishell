/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:03:38 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/08 18:21:47 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	leaks(void)
{
	system("leaks -q minishell");
}

void	init_structs(t_input *in, t_list **envp)
{
	in->env_list = envp;
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

void	update_level(t_input *in)
{
	int		level;
	char	*aux;	
	
	aux = ft_getenv("SHLVL", in);
	level = ft_atoi(aux);
	free(aux);
	level++;
	aux = ft_strjoin("SHLVL=", ft_itoa(level));
	in->split_input = malloc(sizeof(char *) * 3);
	in->split_input[1] = ft_strdup(aux);
	in->split_input[2] = NULL;
	free(aux);
	export(in);
}

int	main(int argc, char **argv, char **environ)
{
	t_input				in;
	t_list				*envp;

	envp = NULL;
	init_env_list(&in, &envp, environ);
	init_structs(&in, &envp);
	update_level(&in);
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
