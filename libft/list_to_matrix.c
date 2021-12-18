/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:34:58 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/14 18:27:09 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**list_to_matrix(t_list *lst)
{
	int		i;
	char	**matrix;
	t_list	*aux;

	i = 0;
	aux = lst;
	matrix = malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	while (aux)
	{
		matrix[i] = ft_strdup(aux->content);
		aux = aux->next;
		i++;
	}
	matrix[i] = NULL;
	return (matrix);
}
