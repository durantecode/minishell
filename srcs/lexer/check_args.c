/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 19:23:22 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/15 11:40:00 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_args(t_input *in)
{
	int		input_size;

	if (!in->user_input)
		return ;
	ft_bzero(&in->flags, sizeof(in->flags));
	input_size = count_tokens(in->user_input, in, 0);
	in->split_input = malloc(sizeof(char *) * (input_size + 1));
	if (!in->split_input)
		return ;
	ft_bzero(&in->flags, sizeof(in->flags));
	count_tokens(in->user_input, in, 1);
	in->split_input[input_size] = NULL;
	expand_vars(in);
}
