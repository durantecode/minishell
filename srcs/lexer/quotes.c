/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:50:08 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/14 13:46:55 by ldurante         ###   ########.fr       */
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

void	update_env_var(t_input *in, char *var, char *value)
{
	char	**aux_in;
	char	*tmp;

	aux_in = NULL;
	if (in->split_input)
		aux_in = matrix_dup(in->split_input); 
	tmp = ft_strjoin(var, value);
	if (in->split_input)
		free_matrix(in->split_input);
	in->split_input = malloc(sizeof(char *) * 3);
	in->split_input[0] = ft_strdup("export");
	in->split_input[1] = tmp;
	in->split_input[2] = NULL;
	export(in);
	free_matrix(in->split_input);
	in->split_input = NULL;
	in->split_input = aux_in;
}

char	**quotes(t_input *in)
{
	int		size;
	int		i;
	char	*aux;

	i = 0;
	while (in->split_input[i] != NULL)
	{
		ft_bzero(&in->flags, sizeof(in->flags));
		aux = delete_quote(in, in->split_input[i]);
		if (!ft_strncmp(in->split_input[i], aux, ft_strlen(aux)))
			in->quote_state[i] = 0;
		else
			in->quote_state[i] = 1;
		free(in->split_input[i]);
		in->split_input[i] = aux;
		i++;
	}
	size = matrix_len(in->split_input);
	update_env_var(in, "_=", in->split_input[size - 1]);
	return (in->split_input);
}
