/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:50:19 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/15 18:03:30 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	split_pipes_aux(t_input *in, char **final_input)
{
	char	c;

	while (in->user_input[in->flags.i] != '\0')
	{
		check_quotes(in);
		if (in->flags.double_q == 0 && in->flags.single_q == 0 && (in->user_input[in->flags.i] == '|' || in->user_input[in->flags.i] == '<' || in->user_input[in->flags.i] == '>'))
		{
			c = in->user_input[in->flags.i];
			if (in->user_input[in->flags.i + 1] != c)
			{
				(*final_input)[in->flags.count++] = ' ';
				(*final_input)[in->flags.count++] = in->user_input[in->flags.i];
				(*final_input)[in->flags.count] = ' ';
			}
			else
			{
				(*final_input)[in->flags.count++] = ' ';
				(*final_input)[in->flags.count++] = in->user_input[in->flags.i];
				(*final_input)[in->flags.count++] = in->user_input[in->flags.i];
				(*final_input)[in->flags.count] = ' ';
				in->flags.i += 1;
			}
		}
		else
		{
			(*final_input)[in->flags.count] = in->user_input[in->flags.i];
		}
		in->flags.count++;
		in->flags.i++;
	}
	// printf("I: %d\n", in->flags.i);
	// printf("END: %d\n", in->flags.count);
}

void	split_pipes(t_input *in)
{
	char	*final_input;
	char	c;

	ft_bzero(&in->flags, sizeof(in->flags));
	while (in->user_input[in->flags.i] != '\0')
	{
		check_quotes(in);
		if (in->flags.double_q == 0 && in->flags.single_q == 0 && (in->user_input[in->flags.i] == '|'
		|| in->user_input[in->flags.i] == '<' || in->user_input[in->flags.i] == '>'))
		{
			c = in->user_input[in->flags.i];
			if (in->user_input[in->flags.i + 1] == c)
				in->flags.i++;
			in->flags.count+= 2;
		}
		in->flags.i++;
	}
	final_input = malloc(sizeof(char) * in->flags.count + in->flags.i + 1);
	in->flags.count = 0;
	in->flags.i = 0;
	split_pipes_aux(in, &final_input);
	final_input[in->flags.count] = '\0';
	free(in->user_input);
	in->user_input = NULL;
	in->user_input = final_input;
}
