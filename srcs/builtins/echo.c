/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:33:35 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/10 20:25:07 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_echo(t_input *in, int i)
{
	while (in->split_input[++i])
	{
		if (in->split_input[i + 1] != NULL)
		{
			write(1, in->split_input[i], ft_strlen(in->split_input[i]));
			write(1, " ", 1);
		}
		else
			write(1, in->split_input[i], ft_strlen(in->split_input[i]));
	}
}

void	echo(t_input *in)
{
	int	i;

	i = 0;
	if (in->split_input[1] == NULL)
		write(1, "\n", 1);
	else if (!(ft_strncmp(in->split_input[1], "-n", 3)))
	{
		i = 1;
		if (in->split_input[i + 1] == NULL)
			return ;
		while (!(ft_strncmp(in->split_input[i], "-n", 3)))
			i++;
		i -= 1;
		print_echo(in, i);
	}
	else
	{
		i = 0;
		print_echo(in, i);
		write(1, "\n", 1);
	}
}
