/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:03:38 by ldurante          #+#    #+#             */
/*   Updated: 2021/11/24 22:37:17 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	leaks(void)
{
	system("leaks minishell");
}

void	init_flags(t_input *in)
{
	in->flags.i = 0;
	in->flags.j = 0;
	in->flags.start = 0;
	in->flags.count = 0;
	in->flags.single_q = 0;
	in->flags.double_q = 0;
	in->flags.global_q = 0;
	in->flags.global_count = 0;
	in->flags.global_sp = 0;
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

int	main(void)
{
	t_input				in;
	t_list				*envp;
	struct sigaction	sa;

	// atexit(leaks);
	if (*environ)
	{
		envp = NULL;
		init_env_list(&envp);
		init_structs(&in, &envp);
		sa.sa_sigaction = catch_signal;
		while (1)
		{
			sigaction(SIGINT, &sa, NULL);
			read_input(&in);
		}
		return (0);
	}
}
