/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:03:38 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/11 14:32:38 by ldurante         ###   ########.fr       */
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

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, &"\n", 1);
	return ;
}

/* REVISAR SHELL LEVEL CUANDO SE HACE UNSET */

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
	free_matrix(in->split_input);
}

int	main(int argc, char **argv, char **environ)
{
	t_input	in;
	t_list	*envp;

	envp = NULL;
	init_env_list(&in, &envp, environ);
	init_structs(&in, &envp);
	update_level(&in);
	if (argc == 1)
	{
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
		in.split_input[0] = argv[1];
		error_msg(&in, ERR_ARG, 1);
	}
	(void)argv;
	return (0);
}
