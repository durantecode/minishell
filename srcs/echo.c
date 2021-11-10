/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:33:35 by ldurante          #+#    #+#             */
/*   Updated: 2021/11/10 13:00:36 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	expand_var(char *str)
{
	char	*var;

	var = getenv(str);
	if (var)
		printf("%s ", var);
}

void	echo(t_input *in)
{
	int i;

	i = 0;
	if (in->split_input[1] == NULL)
		printf("\n");
	else if (!(ft_strncmp(in->split_input[1], "-n", 3)))
	{
		if (in->split_input[2] != NULL)
		{
			i = 1;
			while (in->split_input[++i])
			{
				if (in->split_input[i][0] == '$')
					expand_var(in->split_input[i] + 1);
				else
					printf("%s ", in->split_input[i]);
			}
		}
	}
	else
	{
		i = 0;
		while (in->split_input[++i])
		{
			if (in->split_input[i][0] == '$')
				expand_var(in->split_input[i] + 1);
			else
				printf("%s ", in->split_input[i]);
		}
		printf("\n");
	}
}
