/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:17:33 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/15 16:46:29 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* REVISAR SI HACER FREES EN ESTA FUNCIÓN */

void	my_exit(t_input *in)
{
	if (in->total_pipes == 1)
		printf("%s\n", "exit");
	free_matrix(in->split_input);
	free(in->quote_state);
	ft_lstclear(in->env_list, free);
	free(in->prompt);
	exit(0);
}
