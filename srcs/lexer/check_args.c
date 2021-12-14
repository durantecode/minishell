/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 19:23:22 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/14 12:49:46 by ldurante         ###   ########.fr       */
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
	// printf("%d\n", input_size);
	in->split_input = malloc(sizeof(char *) * (input_size + 1));
	if (!in->split_input)
		return ;
	ft_bzero(&in->flags, sizeof(in->flags));
	count_tokens(in->user_input, in, 1);
	in->split_input[input_size] = NULL;
	//print_matrix(in->split_input);
	expand_vars(in);
}
