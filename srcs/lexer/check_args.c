/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 19:23:22 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/17 18:25:58 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_args(t_input *in)
{
	int		input_size;

	if (!in->user_in)
		return (0);
	ft_bzero(&in->f, sizeof(in->f));
	input_size = count_tokens(in->user_in, in, 0);
	in->split_in = malloc(sizeof(char *) * (input_size + 1));
	in->q_state_size = input_size;
	free(in->q_state);
	in->q_state = malloc(sizeof(int) * in->q_state_size);
	if (!in->split_in)
		return (0);
	ft_bzero(&in->f, sizeof(in->f));
	count_tokens(in->user_in, in, 1);
	in->split_in[input_size] = NULL;
	expand_vars(in);
	return (input_size);
}
