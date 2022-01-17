/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:02:45 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/17 11:58:24 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handler(int	code)
{
	if (code == SIGINT)
	{
		g_exit_status = 1;
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handler2(int code)
{
	if (code == SIGINT)
	{
		write(2, "\n", 1);
		g_exit_status = 130;
	}
	else if (code == SIGQUIT)
	{
		write(2, "Quit: 3\n", 8);
		g_exit_status = 131;
	}
}

void	handler3(int code)
{
	if (code == SIGINT)
		exit(130);
	if (code == SIGQUIT)
		exit(131);
}

void	handler4(int code)
{
	if (code == SIGINT)
		exit(255);
}
