/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:03:38 by ldurante          #+#    #+#             */
/*   Updated: 2021/11/09 17:25:17 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	leaks()
{
	system("leaks minishell");
}

void	read_input(t_input *input)
{
	char	*prompt;

	prompt = ft_strjoin(getenv("USER"), "@minishell$ ");
	input->user_input = readline(prompt);
	input->split_input = ft_split(input->user_input, ' ');
	free(prompt);
	if (input->split_input[0] != NULL)
		builtins(input);
}

int		main(void)
{
	t_input	input;
	struct	sigaction	sa;
	
	atexit(leaks);
	sa.sa_sigaction = catch_signal;
	input.split_path = ft_split(getenv("PATH"), ':');
	while (1)
	{
		sigaction(SIGINT, &sa, NULL);
		read_input(&input);
	}
	return (0);
}
