/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:03:38 by ldurante          #+#    #+#             */
/*   Updated: 2021/11/08 15:43:31 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	leaks()
{
	system("leaks minishell");
}

int		main(void)
{
	char    *prompt;
	char	*string;

	atexit(leaks);
	prompt = ft_strjoin(getenv("USER"), "@minishell% ");
	while (1)
	{
		string = readline(prompt);
		free(string);
	}
	free(prompt);
}

prueba