/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:43:03 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/10 18:16:14 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_tokens(char *s, t_input *in, int split)
{
	int start;

	start = 0;
	if (!split)
	{
		while (s[in->flags.i] != '\0')
		{
			quotes_state(in, s);
			if (s[in->flags.i] == ' ' && !start)
			{
				while (s[in->flags.i] == ' ' && s[in->flags.i])
					in->flags.i++;
				start = 1;
			}
			else if (s[in->flags.i] != ' ')
				start = 1;
			if (s[in->flags.i] == ' ' && in->flags.single_q == 0 && in->flags.double_q == 0)
			{
				if (start)
					in->flags.count++;
				while (s[in->flags.i] == ' ' && s[in->flags.i])
					in->flags.i++;
			}
			else if (s[in->flags.i] != '\0')
			{
				in->flags.i++;
				if (s[in->flags.i] == '\0')
					in->flags.count++;
			}
		}
	}	
	if (split)
	{
		in->flags.i = 0;
		in->flags.start = 0;
		while (s[in->flags.i] != '\0')
		{
			quotes_state(in, s);
			if (s[in->flags.i] == ' ' && !start)
			{
				while (s[in->flags.i] == ' ' && s[in->flags.i])
					in->flags.i++;
				in->flags.start = in->flags.i;
				start = 1;
			}
			else if (s[in->flags.i] != ' ')
				start = 1;
			if (s[in->flags.i] == ' ' && in->flags.single_q == 0 && in->flags.double_q == 0)
			{
				if (start)
				{
					in->split_input[in->flags.j] =
						ft_substr(s, in->flags.start, in->flags.i - in->flags.start);
					in->flags.j++;
				}
				while (s[in->flags.i] == ' ' && s[in->flags.i])
					in->flags.i++;
				in->flags.start = in->flags.i;
			}
			else if (s[in->flags.i] != '\0')
			{
				in->flags.i++;
				if (s[in->flags.i] == '\0')
				{
					in->split_input[in->flags.j] =
						ft_substr(s, in->flags.start, in->flags.i - in->flags.start);
					in->flags.start = in->flags.i;
					in->flags.j++;
				}
			}
		}
	}
	return (in->flags.count);
}
