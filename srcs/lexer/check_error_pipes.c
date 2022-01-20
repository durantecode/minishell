/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_pipes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 10:09:11 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/20 15:54:10 by ldurante         ###   ########.fr       */
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

int	check_errors_pipes_aux(t_input *in)
{
	int		count;
	char	c;

	count = 0;
	c = '\0';
	if (!in->f.double_q && !in->f.single_q)
		c = in->user_in[in->f.i];
	else
		in->f.i++;
	while ((in->user_in[in->f.i] == c || in->user_in[in->f.i] == ' ')
		&& count < 2 && in->user_in[in->f.i])
	{
		if (in->user_in[in->f.i] == c)
			count++;
		in->f.i++;
	}
	if (count >= 2)
		error_msg(in, ERR_SYNTAX_PIPE, -2, 0);
	if (count >= 2)
		return (1);
	return (0);
}

int	check_error_pipes(t_input *in)
{
	int	flag;

	flag = 0;
	while (in->user_in[in->f.i])
	{
		check_quotes(in);
		if (in->user_in[in->f.i] == '|')
		{
			flag = 1;
			if (check_errors_pipes_aux(in))
				return (1);
		}
		else
		{
			if (!char_sp(in->user_in[in->f.i]))
				flag = 0;
			in->f.i++;
		}
	}
	if (in->user_in[0] == '|' || flag == 1)
	{
		error_msg(in, ERR_SYNTAX_PIPE, -2, 0);
		return (1);
	}	
	return (0);
}
