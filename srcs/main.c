/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:03:38 by ldurante          #+#    #+#             */
/*   Updated: 2021/11/10 15:49:22 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	leaks(void)
{
	system("leaks minishell");
}

void	init_structs(t_input *in)
{
	in->user_input = NULL;
	in->split_path = ft_split(getenv("PATH"), ':');
	in->split_input = NULL;
	in->cmd_path = NULL;
}

int	main(void)
{
	t_input	in;
	struct	sigaction	sa;
	
	// atexit(leaks);
	if (*environ)
	{
		init_structs(&in);
		sa.sa_sigaction = catch_signal;
		while (1)
		{
			sigaction(SIGINT, &sa, NULL);
			read_input(&in);
		}
		return (0);
	}
	else
		printf("No environment values\n");
}
