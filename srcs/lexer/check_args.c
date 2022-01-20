/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 19:23:22 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/20 16:44:59 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_error_redirs_aux(t_input *in, int i)
{
	if ((in->split_in[0][0] == '<' || in->split_in[0][0] == '>')
		&& in->split_in[1] == NULL)
		error_msg(in, ERR_SYNTAX, -2, 0);
	else if (in->split_in[i - 1][0] == '<' || in->split_in[i - 1][0] == '>')
		error_msg(in, ERR_SYNTAX, -2, 0);
	if (in->is_err)
		return (1);
	return (0);
}

int	check_error_redirs(t_input *in)
{
	int	i;

	i = -1;
	while (in->split_in[++i])
	{
		if (in->split_in[i + 1] != NULL)
		{
			if (!(ft_strncmp(in->split_in[i], "<", 1))
				&& (in->split_in[i + 1][0] == '|'))
				error_msg(in, ERR_SYNTAX_PIPE, -2, 0);
			else if (!(ft_strncmp(in->split_in[i], ">", 1))
				&& (in->split_in[i + 1][0] == '|'))
				error_msg(in, ERR_SYNTAX_PIPE, -2, 0);
			else if (!(ft_strncmp(in->split_in[i], "<", 1))
				&& !(ft_strncmp(in->split_in[i + 1], "<", 1)))
				error_msg(in, ERR_SYNTAX_IN, -2, 0);
			else if (!(ft_strncmp(in->split_in[i], ">", 1))
				&& !(ft_strncmp(in->split_in[i + 1], ">", 1)))
				error_msg(in, ERR_SYNTAX_OUT, -2, 0);
			if (in->is_err)
				return (1);
		}
	}
	return (check_error_redirs_aux(in, i));
}

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
	if (check_error_redirs(in))
		return (0);
	expand_vars(in);
	return (input_size);
}
