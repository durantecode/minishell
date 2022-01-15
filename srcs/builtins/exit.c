/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:17:33 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/15 14:23:31 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	my_exit(t_input *in)
{
	if (!in->total_pipes)
		printf("%s\n", "exit");
	if (in->split_input[1])
		printf("minishell: exit: too many arguments\n");
	free_matrix(in->split_input);
	//free_matrix(in->dup_env);
	free(in->quote_state);
	ft_lstclear(in->env_list, free);
	free(in->prompt);
	close(0);
	close(1);
	close(2);
	exit(0);
}
