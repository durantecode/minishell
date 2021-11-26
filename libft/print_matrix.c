/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 20:09:45 by ldurante          #+#    #+#             */
/*   Updated: 2021/11/25 22:34:43 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		printf("(null)\n");
	else
	{
		while (matrix[i])
		{
			printf("%s\n", matrix[i]);
			i++;
		}
	}
}