/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:50:19 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/17 12:59:57 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	split_args_aux(t_input *in, char **final_in)
{
	char	c;

	while (in->user_in[in->f.i] != '\0')
	{
		check_quotes(in);
		if (in->f.double_q == 0 && in->f.single_q == 0 && (in->user_in[in->f.i] == '|' || in->user_in[in->f.i] == '<' || in->user_in[in->f.i] == '>'))
		{
			c = in->user_in[in->f.i];
			if (in->user_in[in->f.i + 1] != c)
			{
				(*final_in)[in->f.count++] = ' ';
				(*final_in)[in->f.count++] = in->user_in[in->f.i];
				(*final_in)[in->f.count] = ' ';
			}
			else
			{
				(*final_in)[in->f.count++] = ' ';
				(*final_in)[in->f.count++] = in->user_in[in->f.i];
				(*final_in)[in->f.count++] = in->user_in[in->f.i];
				(*final_in)[in->f.count] = ' ';
				in->f.i += 1;
			}
		}
		else
		{
			(*final_in)[in->f.count] = in->user_in[in->f.i];
		}
		in->f.count++;
		in->f.i++;
	}
}


void	split_args(t_input *in)
{
	char	*final_in;
	char	c;

	ft_bzero(&in->f, sizeof(in->f));
	while (in->user_in[in->f.i] != '\0')
	{
		check_quotes(in);
		if (in->f.double_q == 0 && in->f.single_q == 0 && (in->user_in[in->f.i] == '|'
		|| in->user_in[in->f.i] == '<' || in->user_in[in->f.i] == '>'))
		{
			c = in->user_in[in->f.i];
			if (in->user_in[in->f.i + 1] == c)
				in->f.i++;
			in->f.count+= 2;
		}
		in->f.i++;
	}
	final_in = malloc(sizeof(char) * in->f.count + in->f.i + 1);
	in->f.count = 0;
	in->f.i = 0;
	split_args_aux(in, &final_in);
	final_in[in->f.count] = '\0';
	free(in->user_in);
	in->user_in = NULL;
	in->user_in = final_in;
}
