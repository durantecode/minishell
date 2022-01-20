/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 00:23:56 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/20 10:34:00 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_var_aux(t_input *in)
{
	if (in->f.i > 1 && in->split_in[in->f.j][in->f.i] == '"'
		&& in->split_in[in->f.j][in->f.i - 2] == '"')
		return (2);
	if (in->split_in[in->f.j][in->f.i] == '"' && !in->f.double_q)
		return (2);
	if (in->split_in[in->f.j][in->f.i] == '"' && in->f.double_q)
		return (1);
	if (in->split_in[in->f.j][in->f.i] == '\'' && !in->f.single_q
		&& !in->f.double_q)
		return (1);
	if (in->split_in[in->f.j][in->f.i] == '\'' && in->f.single_q
		&& !in->f.double_q)
		return (1);
	if (in->split_in[in->f.j][in->f.i] == '?')
	{
		in->f.i--;
		return (0);
	}
	if (in->split_in[in->f.j][in->f.i] == '_')
	{
		in->f.i--;
		return (0);
	}
	else
		return (2);
}

int	check_var(t_input *in)
{
	in->f.i++;
	quotes_state(in, in->split_in[in->f.j]);
	if (!ft_isalnum(in->split_in[in->f.j][in->f.i]))
	{
		if (in->split_in[in->f.j][in->f.i] == '\0')
		{
			in->f.i--;
			return (2);
		}
		if (in->split_in[in->f.j][in->f.i] == '$')
		{
			if (ft_isalnum(in->split_in[in->f.j][in->f.i + 1])
				&& in->split_in[in->f.j][in->f.i + 1] != '\0')
				return (0);
			return (2);
		}
		return (check_var_aux(in));
	}
	in->f.i--;
	return (0);
}

void	expand_vars_aux(t_input *in)
{
	int		check;
	char	*aux;
	char	*var;

	check = check_var(in);
	if (check == 1)
	{
		aux = del_str_pos(in->split_in[in->f.j], in->f.i - 1);
		free(in->split_in[in->f.j]);
		in->split_in[in->f.j] = ft_strdup(aux);
		free(aux);
	}
	else if (check == 0)
	{
		aux = ft_substr(in->split_in[in->f.j], 0, in->f.i);
		var = get_expanded_var(in->split_in[in->f.j], in->f.i + 1);
		insert_exp_var(in, &var, &aux, in->f.j);
		in->f.i = in->f.count - 1;
	}
}

void	expand_vars(t_input *in)
{
	ft_bzero(&in->f, sizeof(in->f));
	while (in->split_in[in->f.j] != NULL)
	{
		in->f.i = 0;
		while (in->split_in[in->f.j][in->f.i] != '\0')
		{
			quotes_state(in, in->split_in[in->f.j]);
			if (in->split_in[in->f.j][in->f.i] == '$' && !in->f.single_q)
				expand_vars_aux(in);
			in->f.i++;
		}
		in->f.j++;
	}
	in->split_in = quotes(in);
}
