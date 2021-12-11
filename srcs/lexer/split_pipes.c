/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:50:19 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/11 00:25:04 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	split_pipes_aux(t_input *in, char **final_input)
{
	while (in->user_input[in->flags.i])
	{
		if ((in->user_input[in->flags.i] == '"'
				|| in->user_input[in->flags.i] == '\'')
			&& in->flags.global_q == 0)
			in->flags.global_q = 1;
		else if ((in->user_input[in->flags.i] == '"'
				|| in->user_input[in->flags.i] == '\'')
			&& in->flags.global_q == 1)
			in->flags.global_q = 0;
		if (in->flags.global_q == 0 && (in->user_input[in->flags.i] == '|' || in->user_input[in->flags.i] == '<' || in->user_input[in->flags.i] == '>'))
		{
			(*final_input)[in->flags.count++] = ' ';
			(*final_input)[in->flags.count++] = in->user_input[in->flags.i];
			(*final_input)[in->flags.count] = ' ';
		}
		else
			(*final_input)[in->flags.count] = in->user_input[in->flags.i];
		in->flags.count++;
		in->flags.i++;
	}
}

char	*split_pipes(t_input *in)
{
	char	*final_input;

	ft_bzero(&in->flags, sizeof(in->flags));
	while (in->user_input[in->flags.i])
	{
		if ((in->user_input[in->flags.i] == '"'
				|| in->user_input[in->flags.i] == '\'')
			&& in->flags.global_q == 0)
			in->flags.global_q = 1;
		else if ((in->user_input[in->flags.i] == '"'
				|| in->user_input[in->flags.i] == '\'')
			&& in->flags.global_q == 1)
			in->flags.global_q = 0;
		if (in->flags.global_q == 0 && (in->user_input[in->flags.i] == '|' || in->user_input[in->flags.i] == '<' || in->user_input[in->flags.i] == '>'))
			in->flags.count += 2;
		in->flags.count++;
		in->flags.i++;
	}
	final_input = malloc(sizeof(char) * in->flags.count + 1);
	in->flags.count = 0;
	in->flags.i = 0;
	split_pipes_aux(in, &final_input);
	final_input[in->flags.count] = '\0';
	return (final_input);
}
