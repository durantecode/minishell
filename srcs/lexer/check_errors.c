/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 12:24:49 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/17 12:36:19 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_quotes(t_input *in)
{
	if (in->user_in[in->f.i] == '"' && !in->f.single_q
		&& !in->f.double_q)
		in->f.double_q = 1;
	else if (in->user_in[in->f.i] == '"' && !in->f.single_q
		&& in->f.double_q)
		in->f.double_q = 0;
	else if (in->user_in[in->f.i] == '\'' && !in->f.single_q
		&& !in->f.double_q)
		in->f.single_q = 1;
	else if (in->user_in[in->f.i] == '\'' && in->f.single_q
		&& !in->f.double_q)
		in->f.single_q = 0;
}

int	check_errors2(t_input *in)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (in->user_in[i])
	{
		if (in->user_in[i] != ' ' && in->user_in[i] != '|')
			flag = 1;
		if (in->user_in[i] == '|' && flag == 0)
		{
			error_msg(in, ERR_SYNTAX, -1, 0);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_errors(t_input *in)
{
	char	c;
	int		count;
	int		flag_diff;
	int		special;

	special = 0;
	flag_diff = 0;
	while (in->user_in[in->f.i])
	{
		count = 0;
		check_quotes(in);
		if (in->f.double_q == 0 && in->f.single_q == 0)
		{
			if (in->user_in[in->f.i] == '<' || in->user_in[in->f.i] == '>' || in->user_in[in->f.i] == '|' || char_space(in->user_in[in->f.i]))
			{
				if (in->user_in[in->f.i] == '<' || in->user_in[in->f.i] == '>' || in->user_in[in->f.i] == '|')
				{
					if (in->user_in[in->f.i] == '|' && special == 1 && flag_diff == 0)
					{
						error_msg(in, ERR_SYNTAX, -2, 0);
						return (1);
					}
					else if (in->user_in[in->f.i] == '|')
					{
						count = 0;
						flag_diff = 0;
					}
					special = 1;
				}
				c = in->user_in[in->f.i];
				while (c == in->user_in[in->f.i++] && count <= 2)
				{
					count++;
					in->f.i++;
				}
				while (char_space(in->user_in[in->f.i]))
					in->f.i++;
				if (((c == '<' || c == '>') && count > 2)
					|| (c == '|' && count > 1)
					|| in->user_in[in->f.i] == c)
				{
					error_msg(in, ERR_SYNTAX, -2, 0);
					return (1);
				}
			}
			else
			{
				flag_diff = 1;
				in->f.i++;
			}
		}
		else
			in->f.i++;
	}
	if (flag_diff == 0 && special == 1)
	{
		error_msg(in, ERR_SYNTAX, -2, 0);
		return (1);
	}
	return (check_errors2(in));
}