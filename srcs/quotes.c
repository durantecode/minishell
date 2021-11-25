/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:50:08 by ldurante          #+#    #+#             */
/*   Updated: 2021/11/25 19:29:53 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	quotes_aux(t_input *in, char *str)
{
	if (str[in->flags.i] == '"'
		&& in->flags.single_q == 0 && in->flags.double_q == 0)
	{
		in->flags.double_q = 1;
		return (1);
	}
	else if (str[in->flags.i] == '"'
		&& in->flags.single_q == 0 && in->flags.double_q == 1)
	{	
		in->flags.double_q = 0;
		return (1);
	}
	else if (str[in->flags.i] == '\''
		&& in->flags.single_q == 0 && in->flags.double_q == 0)
	{
		in->flags.single_q = 1;
		return (1);
	}
	else if (str[in->flags.i] == '\''
		&& in->flags.single_q == 1 && in->flags.double_q == 0)
	{
		in->flags.single_q = 0;
		return (1);
	}
	return (0);
}

static char	*delete_quote(t_input *in, char *str)
{
	char	*str_final;

	while (str[in->flags.i])
	{
		if (!quotes_aux(in, str))
			in->flags.j++;
		in->flags.i++;
	}
	str_final = malloc(sizeof(char) * (in->flags.j + 1));
	str_final[in->flags.j] = '\0';
	ft_bzero(&in->flags, sizeof(in->flags));
	while (str[in->flags.i])
	{
		if (!quotes_aux(in, str))
			str_final[in->flags.j++] = str[in->flags.i];
		in->flags.i++;
	}
	return (str_final);
}

char	**quotes(t_input *in)
{
	int		i;
	char	*aux;

	i = 0;
	while (in->split_input[i] != NULL)
	{
		aux = in->split_input[i];
		ft_bzero(&in->flags, sizeof(in->flags));
		in->split_input[i] = delete_quote(in, in->split_input[i]);
		free(aux);
		i++;
	}
	return (in->split_input);
}
