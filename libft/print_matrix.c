/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 20:09:45 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/19 11:18:52 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		ft_printf("(null)\n");
	else
	{
		while (matrix[i])
		{
			ft_printf("%s\n", matrix[i]);
			i++;
		}
	}
}
