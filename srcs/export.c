/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:30:13 by ldurante          #+#    #+#             */
/*   Updated: 2021/11/24 17:49:07 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	export(t_input *in)
{
	int	last;

	last = ft_strlen(in->split_input[1]);
	if (in->split_input[1][last - 1] == '=')
		printf("HI\n");
}
