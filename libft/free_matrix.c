/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:35:10 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/15 12:36:19 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	free_matrix(char ***m)
// {
// 	int	i;

// 	i = 0;
// 	while (m && m[0] && m[0][i])
// 	{
// 		free(m[0][i]);
// 		i++;
// 	}
// 	if (m)
// 	{
// 		free(m[0]);
// 		*m = NULL;
// 	}
// }

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}
