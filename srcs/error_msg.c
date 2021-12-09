/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:58:27 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/09 18:54:25 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		error_msg(t_input *in, char *ERR, int n)
{
	if (n == 1)
		printf("%s: %s: %s", SHELL, in->split_input[0], ERR);
	else
		printf("%s: %s", SHELL, ERR);
	(void)in;
	return (0);
}