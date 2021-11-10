/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:03:38 by ldurante          #+#    #+#             */
/*   Updated: 2021/11/09 21:30:46 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	leaks()
{
	system("leaks minishell");
}

char	**check_quotes(char **user_input)
{
	int i;
	int	last;
	int len;

	i = 0;
	while (user_input[i] != NULL)
	{
		len = ft_strlen(user_input[i]);
		last = len - 1;
		if (user_input[i][0] == '"' && user_input[i][last] == '"')
			user_input[i] = ft_substr(user_input[i], 1, len - 2);
		if (user_input[i][0] == '\'' && user_input[i][last] == '\'')
			user_input[i] = ft_substr(user_input[i], 1, len - 2);
		i++;
	}
	return (user_input);
}

void	read_input(t_input *input)
{
	char	*prompt;

	prompt = ft_strjoin(getenv("USER"), "@minishell$ ");
	input->user_input = readline(prompt);
	add_history(input->user_input);
	input->split_input = ft_split(input->user_input, ' ');
	check_quotes(input->split_input);
	free(prompt);
	if (input->split_input[0] != NULL)
		builtins(input);
}

int		main(void)
{
	t_input	input;
	struct	sigaction	sa;
	
	// atexit(leaks);
	sa.sa_sigaction = catch_signal;
	input.split_path = ft_split(getenv("PATH"), ':');
	while (1)
	{
		sigaction(SIGINT, &sa, NULL);
		read_input(&input);
	}
	return (0);
}
