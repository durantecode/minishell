/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:03:38 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/17 15:45:07 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	Mirar que se inicializan correctamente todas las variables al iniciar el programa.
*/

int	g_exit_status;

void	leaks(void)
{
	system("leaks -q minishell");
}

void	init_structs(t_input *in, t_list **envp)
{
	in->env_list = envp;
	in->user_in = NULL;
	in->split_in = NULL;
	in->cmd_path = NULL;
	in->is_infile = 0;
	in->fd_in = 0;
	in->fd_out = 0;
	in->fd_error = 2;
	in->status = 0;
	g_exit_status = 0;
}

void	update_level(t_input *in)
{
	int		level;
	char	*number;
	char	*aux;	

	aux = ft_getenv("SHLVL", in);
	level = ft_atoi(aux);
	if (level < 0)
	{
		ft_putstr_fd(SHELL, 2);
		if (level == -1)
			level++;
		ft_putendl_fd(ERR_SHLVL, 2);
	}
	free(aux);
	level++;
	number = ft_itoa(level);
	update_env_var(in, "SHLVL=", number);
	free(number);
}

int	main(int argc, char **argv, char **environ)
{
	t_input	in;
	t_list	*envp;

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
			unlink(".hd_tmp");
			unlink(".err_tmp");
		}
	}
	else
	{
		in.split_in = argv;
		error_msg(&in, ERR_ARG, -1, 0);
	}
	return (0);
}
