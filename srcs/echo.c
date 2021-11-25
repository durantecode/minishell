/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:33:35 by ldurante          #+#    #+#             */
/*   Updated: 2021/11/25 00:27:46 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	expand_var(char *str, t_input *in)
{
	char	*var;

	var = ft_getenv(str, in);
	if (var)
		printf("%s ", var);
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
		while (in->split_input[++i])
			printf("%s ", in->split_input[i]);
	}
	else
	{
		i = 0;
		while (in->split_input[++i])
			printf("%s ", in->split_input[i]);
		printf("\n");
	}
}
