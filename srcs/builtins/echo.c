/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:33:35 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/17 12:00:09 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_echo(t_input *in, int i)
{
	while (in->split_in[i])
	{
		if (in->split_in[i + 1] != NULL)
		{
			write(1, in->split_in[i], ft_strlen(in->split_in[i]));
			write(1, " ", 1);
		}
		else
			write(1, in->split_in[i], ft_strlen(in->split_in[i]));
		i++;
	}
}

int		is_n(char *str)
{
	int i;

	i = 1;
	while(str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}	

void	echo(t_input *in)
{
	int	i;

	i = 0;
	if (in->split_in[1] == NULL)
		write(1, "\n", 1);
	else if (!(ft_strncmp(in->split_in[1], "-n", 3)))
	{
		i = 1;
		if (in->split_in[i + 1] == NULL)
			return ;
		while (!(ft_strncmp(in->split_in[i], "-n", 3)) && in->split_in[i])
			i++;
		print_echo(in, i);
	}
	else if (!(ft_strncmp(in->split_in[1], "-n", 2)) && is_n(in->split_in[1]))
	{
		i = 1;
		if (in->split_in[i + 1] == NULL)
			return ;
		while (in->split_in[i])
		{	
			if (!is_n(in->split_in[i]))
				break ;
			i++;
		}
		print_echo(in, i);
	}
	else
	{
		print_echo(in, 1);
		write(1, "\n", 1);
	}
}
