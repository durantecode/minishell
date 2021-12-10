/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:33:35 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/10 16:34:12 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_echo(t_input *in, int i)
{
	while (in->split_input[++i])
	{
		if (in->split_input[i + 1] != NULL)
			printf("%s ", in->split_input[i]);
		else
			printf("%s", in->split_input[i]);
	}
}

void	echo(t_input *in)
{
	int	i;

	i = 0;
	if (in->split_input[1] == NULL)
		printf("\n");
	else if (!(ft_strncmp(in->split_input[1], "-n", 3)))
	{
		i = 1;
		while (!(ft_strncmp(in->split_input[i], "-n", 3)))
			i++;
		i -= 1;
		print_echo(in, i);
	}
	else
	{
		i = 0;
		print_echo(in, i);
		printf("\n");
	}
}
