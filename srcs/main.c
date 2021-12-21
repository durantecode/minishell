/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:03:38 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/19 23:47:41 by ldurante         ###   ########.fr       */
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
	in->n_bytes = 0;
}

void	update_level(t_input *in)
{
	int		level;
	char	*number;
	char	*aux;	

	aux = ft_getenv("SHLVL", in);
	level = ft_atoi(aux);
	free(aux);
	level++;
	number = ft_itoa(level);
	aux = ft_strjoin("SHLVL=", number);
	in->split_input = malloc(sizeof(char *) * 3);
	in->split_input[0] = ft_strdup("export");
	in->split_input[1] = aux;
	in->split_input[2] = NULL;
	free(number);
	export(in);
	free_matrix(in->split_input);
}

void	handler(int	code)
{
	if (code == SIGINT)
	{
		printf("\n");
	}
}

int	main(int argc, char **argv, char **environ)
{
	t_input	in;
	t_list	*envp;

	// atexit(leaks);
	envp = NULL;
	if (argc == 1)
	{
		//print_matrix(environ);
		init_env_list(&in, &envp, environ);
		init_structs(&in, &envp);
		update_level(&in);
		// signal(SIGQUIT, handler);
		// signal(SIGINT, handler);
		while (1)
		{
			if (!isatty(STDIN_FILENO))
			{
				ioctl(STDIN_FILENO, FIONREAD, &in.n_bytes);
				if (in.n_bytes < 1)
					exit (0);
			}
			read_input(&in);
		}
	}
	else
	{
		in.split_input = argv;
		error_msg(&in, ERR_ARG, -1);
	}
	return (0);
}
