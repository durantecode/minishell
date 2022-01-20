/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:43:03 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/19 18:15:07 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	char_sp(char c)
{
	if (c != '\t' && c != ' ' && c != '\n'
		&& c != '\f' && c != '\v' && c != '\r')
		return (0);
	return (1);
}

void	count_tokens_aux(t_input *in, char *s, int start)
{
	while (s[in->f.i] != '\0')
	{
		quotes_state(in, s);
		if (char_sp(s[in->f.i]) && !start)
		{
			while (char_sp(s[in->f.i]) && s[in->f.i])
				in->f.i++;
			start = 1;
		}
		else if (!char_sp(s[in->f.i]))
			start = 1;
		if (char_sp(s[in->f.i]) && !in->f.single_q && !in->f.double_q)
		{
			if (start)
				in->f.count++;
			while (char_sp(s[in->f.i]) && s[in->f.i])
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

void	count_tokens_aux2(t_input *in, char *s, int start)
{
	if (char_sp(s[in->f.i]) && !in->f.single_q && !in->f.double_q)
	{
		if (start)
		{
			in->split_in[in->f.j]
				= ft_substr(s, in->f.start, in->f.i - in->f.start);
			in->f.j++;
		}
		while (char_sp(s[in->f.i]) && s[in->f.i])
			in->f.i++;
		in->f.start = in->f.i;
	}
	else if (s[in->f.i] != '\0')
	{
		in->f.i++;
		if (s[in->f.i] == '\0')
		{
			in->split_in[in->f.j]
				= ft_substr(s, in->f.start, in->f.i - in->f.start);
		}
	}
}

int	count_tokens(char *s, t_input *in, int split)
{
	int	start;

	start = 0;
	if (!split)
		count_tokens_aux(in, s, start);
	if (split)
	{
		in->f.i = 0;
		in->f.start = 0;
		while (s[in->f.i] != '\0')
		{
			quotes_state(in, s);
			if (char_sp(s[in->f.i]) && !start)
			{
				while (char_sp(s[in->f.i]) && s[in->f.i])
					in->f.i++;
				in->f.start = in->f.i;
				start = 1;
			}
			else if (!char_sp(s[in->f.i]))
				start = 1;
			count_tokens_aux2(in, s, start);
		}
	}
	return (in->f.count);
}
