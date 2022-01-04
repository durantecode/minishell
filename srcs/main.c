/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:03:38 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/04 20:05:18 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int exit_status;

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
	in->is_infile = 0;
	in->fd_in = 0;
	in->fd_out = 0;
	exit_status = 0;
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
	update_env_var(in, "SHLVL=", number);
	// aux = ft_strjoin("SHLVL=", number);
	// in->split_input = malloc(sizeof(char *) * 3);
	// in->split_input[0] = ft_strdup("export");
	// in->split_input[1] = aux;
	// in->split_input[2] = NULL;
	// free(number);
	// export(in);
	// free_matrix(in->split_input);
	// in->split_input = NULL;
}

void	handler(int	code)
{
	if (code == SIGINT)
	{
		exit_status = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("",0);
		rl_redisplay();
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
		init_env_list(&in, &envp, environ);
		init_structs(&in, &envp);
		check_basic_vars(&in);
		update_level(&in);
		while (1)
		{
			signal(SIGINT, handler);
			signal(SIGQUIT, SIG_IGN);
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
