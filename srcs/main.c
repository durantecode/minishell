/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:03:38 by ldurante          #+#    #+#             */
/*   Updated: 2021/11/08 21:09:39 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	leaks()
{
	system("leaks minishell");
}

void	to_read(t_input *input)
{
	char	*prompt;

	prompt = ft_strjoin(getenv("USER"), "@minishell$ ");
	input->user_input = readline(prompt);
	input->split_input = ft_split(input->user_input, ' ');
	free(prompt);
	builtins(input);
	// get_builtins(input);
}

int		main(void)
{
	t_input input;
	int i;
	//atexit(leaks);
	i = -1;
	input.split_path = ft_split(getenv("PATH"), ':');
	while (1)
	{
		to_read(&input);
	}
	return (0);
}