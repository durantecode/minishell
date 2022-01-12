/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:17:33 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/12 12:06:37 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	my_exit(t_input *in)
{
	if (in->total_pipes == 1)
		printf("%s\n", "exit");
	if (in->split_input[1])
		printf("minishell: exit: too many arguments\n");
	free_matrix(in->split_input);
	free(in->quote_state);
	ft_lstclear(in->env_list, free);
	free(in->prompt);
	exit(0);
}
