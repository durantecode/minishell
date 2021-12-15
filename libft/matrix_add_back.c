/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_add_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 22:28:01 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/15 12:26:18 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**matrix_add_back(char **matrix, char *str)
{
	char	**out;
	int		len;
	int		i;

	i = -1;
	out = NULL;
	if (!str)
		return (matrix);
	len = matrix_len(matrix);
	out = malloc(sizeof(char *) * (len + 2));
	out[len + 1] = NULL;
	if (!out)
		return (matrix);
	while (++i < len && matrix[i] != NULL)
	{
		out[i] = ft_strdup(matrix[i]);
		if (!out[i])
		{
			free_matrix(matrix);
			free_matrix(out);
		}
	}
	out[i] = ft_strdup(str);
	free_matrix(matrix);
	return (out);
}
