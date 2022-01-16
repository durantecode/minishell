/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_matrix_pos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 19:57:06 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/22 19:57:41 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**del_matrix_pos(char **matrix, int pos)
{
	int		i;
	int		j;
	char	**aux;

	i = 0;
	j = 0;
	aux = malloc(matrix_len(matrix));
	while (matrix[i])
	{
		if (i == pos)
			i++;
		aux[j] = matrix[i];
		i++;
		j++;
	}
	aux[j] = NULL;
	return (aux);
}
