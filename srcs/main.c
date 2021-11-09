/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:03:38 by ldurante          #+#    #+#             */
/*   Updated: 2021/11/09 01:41:26 by ldurante         ###   ########.fr       */
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
	builtins(input);
	exec_cmd(input);
}

int		main(void)
{
	t_input input;

	//atexit(leaks);
	input.split_path = ft_split(getenv("PATH"), ':');
	while (1)
	{
		input.builtin_executed = 0;
		read_input(&input);
	}
	return (0);
}
