/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:33:35 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/08 01:24:14 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Revisar flags -n múltiples */

void	echo(t_input *in)
{
	int	i;

	i = 0;
	if (in->split_input[1] == NULL)
		printf("\n");
	else if (!(ft_strncmp(in->split_input[1], "-n", 3)))
	{
		i = 1;
		while (in->split_input[++i])
			printf("%s", in->split_input[i]);
			// ft_putstr_fd(in->split_input[i], 2);
	}
	else
	{
		i = 0;
		while (in->split_input[++i])
			// ft_putstr_fd(in->split_input[i], 2);
			printf("%s", in->split_input[i]);
		// ft_putchar_fd('\n', 2);
		printf("\n");
	}
}
