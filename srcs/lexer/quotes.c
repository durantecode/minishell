/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:50:08 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/19 23:05:26 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	quotes_state(t_input *in, char *str)
{
	if (str[in->flags.i] == '"'
		&& !in->flags.single_q && !in->flags.double_q)
	{
		in->flags.double_q = 1;
		return (1);
	}
	else if (str[in->flags.i] == '"'
		&& !in->flags.single_q && in->flags.double_q)
	{	
		in->flags.double_q = 0;
		return (1);
	}
	else if (str[in->flags.i] == '\''
		&& !in->flags.single_q && !in->flags.double_q)
	{
		in->flags.single_q = 1;
		return (1);
	}
	else if (str[in->flags.i] == '\''
		&& in->flags.single_q && !in->flags.double_q)
	{
		in->flags.single_q = 0;
		return (1);
	}
	return (0);
}

static char	*delete_quote(t_input *in, char *str)
{
	char	*final_str;

	while (str[in->flags.i])
	{
		if (!quotes_state(in, str))
			in->flags.j++;
		in->flags.i++;
	}
	final_str = malloc(sizeof(char) * (in->flags.j + 1));
	final_str[in->flags.j] = '\0';
	ft_bzero(&in->flags, sizeof(in->flags));
	while (str[in->flags.i])
	{
		if (!quotes_state(in, str))
			final_str[in->flags.j++] = str[in->flags.i];
		in->flags.i++;
	}
	return (final_str);
}

char	**remove_space(t_input *in)
{
	int i;
	int size;
	char *aux;

	i = 0;
	while (in->split_input[i] != NULL)
	{
		size = ft_strlen(in->split_input[i]);
		if (!ft_isascii(in->split_input[i][0]))
		{
			aux = ft_substr(in->split_input[i], 2, size - 1);
			// free(in->split_input[i]);
			in->split_input[i] = ft_strdup(aux);
			free(aux);
		}	
		i++;
	}
	return (in->split_input);
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
	remove_space(in);
	return (in->split_input);
}
