/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:43:03 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/17 13:32:20 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	char_space(char c)
// {
// 	if (c != '\t' && c != ' ' && c != '\n'
// 		&& c != '\f' && c != '\v' && c != '\r')
// 		return (0);
// 	return (1);
// }

int	count_tokens(char *s, t_input *in, int split)
{
	int start;

	start = 0;
	if (!split)
	{
		while (s[in->f.i] != '\0')
		{
			quotes_state(in, s);
			if (char_space(s[in->f.i]) && !start)
			{
				while (char_space(s[in->f.i]) && s[in->f.i])
					in->f.i++;
				start = 1;
			}
			else if (!char_space(s[in->f.i]))
				start = 1;
			if (char_space(s[in->f.i]) && in->f.single_q == 0 && in->f.double_q == 0)
			{
				if (start)
					in->f.count++;
				while (char_space(s[in->f.i]) && s[in->f.i])
					in->f.i++;
			}
			else if (s[in->f.i] != '\0')
			{
				in->f.i++;
				if (s[in->f.i] == '\0')
					in->f.count++;
			}
		}
	}	
	if (split)
	{
		in->f.i = 0;
		in->f.start = 0;
		while (s[in->f.i] != '\0')
		{
			quotes_state(in, s);
			if (char_space(s[in->f.i]) && !start)
			{
				while (char_space(s[in->f.i]) && s[in->f.i])
					in->f.i++;
				in->f.start = in->f.i;
				start = 1;
			}
			else if (!char_space(s[in->f.i]))
				start = 1;
			if (char_space(s[in->f.i]) && in->f.single_q == 0 && in->f.double_q == 0)
			{
				if (start)
				{
					in->split_in[in->f.j] =
						ft_substr(s, in->f.start, in->f.i - in->f.start);
					in->f.j++;
				}
				while (char_space(s[in->f.i]) && s[in->f.i])
					in->f.i++;
				in->f.start = in->f.i;
			}
			else if (s[in->f.i] != '\0')
			{
				in->f.i++;
				if (s[in->f.i] == '\0')
				{
					in->split_in[in->f.j] =
						ft_substr(s, in->f.start, in->f.i - in->f.start);
				}
			}
		}
	}
	return (in->f.count);
}
