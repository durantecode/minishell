/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:43:03 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/10 16:35:14 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	double_quotes(t_input *in, const char *s)
{
	while (s[in->flags.i] != '"' && s[in->flags.i] != '\0')
		in->flags.i++;
	in->flags.double_q = 0;
	if (!in->flags.double_q && s[in->flags.i + 1] != ' ')
	{
		while (s[in->flags.i] && s[in->flags.i] != ' ')
			in->flags.i++;
		in->flags.count++;
		in->flags.global_count = 1;
	}
	else
	{
		in->flags.count++;
		in->flags.global_count = 1;
	}
}

void	single_quotes(t_input *in, const char *s)
{
	while (s[in->flags.i] != '\'' && s[in->flags.i] != '\0')
		in->flags.i++;
	in->flags.single_q = 0;
	if (!in->flags.single_q && s[in->flags.i + 1] != ' ')
	{
		while (s[in->flags.i] && s[in->flags.i] != ' ')
			in->flags.i++;
		in->flags.count++;
		in->flags.global_count = 1;
	}
	else
	{
		in->flags.count++;
		in->flags.global_count = 1;
	}
}

void	split_args(t_input *in, const char *s)
{
	if (!in->flags.global_q)
	{
		if (s[in->flags.i - 1] != ' ')
			in->split_input[in->flags.j] = ft_substr(s, in->flags.start,
					in->flags.i - in->flags.start);
		else
			in->split_input[in->flags.j] = ft_substr(s, in->flags.start,
					in->flags.i - in->flags.start - 1);
	}
	else if (in->flags.global_sp)
	{
		in->split_input[in->flags.j] = ft_substr(s, in->flags.start,
				in->flags.i - in->flags.start);
		in->flags.global_sp = 0;
		in->flags.global_q = 0;
	}	
	if (in->split_input[in->flags.j])
		in->flags.j++;
	in->flags.global_count = 0;
}

void	token_aux(t_input *in, const char *s, int split, int n)
{
	if (n == 0)
	{
		if (s[in->flags.i] != ' ' && s[in->flags.i] != '\0')
		{
			in->flags.count++;
			while (s[in->flags.i] != ' ' && s[in->flags.i])
				in->flags.i++;
			in->flags.global_count = 1;
		}
	}
	if (n == 1)
	{
		if (s[in->flags.i])
			in->flags.i++;
		if (split == 1 && in->flags.global_count)
			split_args(in, s);
		if (!in->flags.global_q)
			in->flags.start = in->flags.i;
	}
}

int	count_tokens(const char *s, t_input *in, int split)
{
	while (s[in->flags.i] != '\0')
	{
		if (s[in->flags.i] == '\'' && in->flags.double_q == 0)
		{
			in->flags.single_q = 1;
			in->flags.global_q = 1;
		}
		else if (s[in->flags.i] == '"' && in->flags.single_q == 0)
		{
			in->flags.double_q = 1;
			in->flags.global_q = 1;
		}
		else if (in->flags.double_q || in->flags.single_q)
		{
			if (in->flags.double_q)
				double_quotes(in, s);
			if (in->flags.single_q)
				single_quotes(in, s);
			in->flags.global_sp = 1;
		}
		else
			token_aux(in, s, split, 0);
		token_aux(in, s, split, 1);
	}
	return (in->flags.count);
}
