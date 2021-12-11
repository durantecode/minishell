/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 03:03:21 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/11 14:54:30 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_redirs(t_input *in)
{
	int i;
	
	i = 0;
	while(in->split_input[i])
	{
		if (!(ft_strncmp(in->split_input[i], "<", 2)))
		{
			if (!(ft_strncmp(in->split_input[i + 1], "<", 2)))
				here_doc(in, i);
			// else
		}
		i++;
	}
}
