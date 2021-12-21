/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:58:27 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/19 23:46:59 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	error_msg(t_input *in, char *MSG, int n)
{
	if (n >= 0)
		printf("%s: %s: %s\n", SHELL, in->split_input[n], MSG);
	// else if (n == 1)
	// 	printf("%s: %s: %s\n", SHELL, in->split_input[1], MSG);
	else
		printf("%s: %s\n", SHELL, MSG);
	return (0);
}
