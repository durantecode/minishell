/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:17:33 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/15 12:24:39 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* REVISAR SI HACER FREES EN ESTA FUNCIÓN */

void	my_exit(t_input *in)
{
	if (in->total_pipes == 1)
		printf("%s\n", "exit");
	free_matrix(in->split_input);
	ft_lstclear(in->env_list, free);
	free(in->prompt);
	exit(0);
}
