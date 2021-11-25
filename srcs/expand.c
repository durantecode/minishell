/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 00:23:56 by ldurante          #+#    #+#             */
/*   Updated: 2021/11/25 00:59:02 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	insert_var(t_input *in, char *var, char *first, int i)
{
	int		len1;
	int		len2;
	int		len3;
	char	*last;
	char	*expanded;

	len1 = ft_strlen(first);
	len2 = ft_strlen(var);
	len3 = ft_strlen(in->split_input[i]);
	last = ft_substr(in->split_input[i], len1 + len2 + 1, len3 - len2 - len1);
	expanded = ft_getenv(var, in);
	if (!expanded)
		expanded = ft_strdup("");
	in->split_input[i] = ft_strjoin3(first, expanded, last);
	free(last);
	free(expanded);
	free(var);
	free(first);
}

void	expand_flags(t_input *in)
{
	if (in->split_input[in->flags.i][in->flags.j] == '"'
			&& !in->flags.single_q)
	{
		if (!in->flags.double_q)
			in->flags.single_q += 2;
		else
			in->flags.single_q++;
	}
	if (in->split_input[in->flags.i][in->flags.j] == '\'')
	{
		in->flags.double_q++;
		if (!in->flags.single_q)
			in->flags.single_q++;
	}
}

void	replace_var(t_input *in, int front)
{
	char	*var;
	char	*first;

	in->flags.j++;
	while (ft_isalnum(in->split_input[in->flags.i][in->flags.j]))
		in->flags.j++;
	var = ft_substr(in->split_input[in->flags.i],
			front + 1, in->flags.j - 1 - front);
	first = ft_substr(in->split_input[in->flags.i], 0, front);
	insert_var(in, var, first, in->flags.i);
}

void	expand_vars(t_input *in)
{
	int	front;

	init_flags(in);
	while (in->split_input[in->flags.i] != NULL)
	{
		in->flags.j = 0;
		in->flags.single_q = 0;
		in->flags.double_q = 0;
		front = 0;
		while (in->split_input[in->flags.i][in->flags.j] != '\0')
		{
			front = in->flags.j;
			expand_flags(in);
			if (in->split_input[in->flags.i][in->flags.j] == '$'
				&& in->flags.single_q % 2 == 0)
				replace_var(in, front);
			in->flags.j++;
		}
		in->flags.i++;
	}
}
