/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:33:35 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/04 19:16:20 by dpavon-g         ###   ########.fr       */
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
	}
	else
	{
		i = 0;
		while (in->split_input[++i])
			printf("%s", in->split_input[i]);
		printf("\n");
	}
}
