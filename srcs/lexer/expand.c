/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 00:23:56 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/11 15:34:34 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* REVISAR FREES, NORMA */

int str_is_digit(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' && str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

void	insert_var(t_input *in, char **var, char **aux, int j)
{
	int		len1;
	int		len2;
	int		len3;
	char	*last;
	char	*expanded;

	len1 = ft_strlen(*aux);
	len2 = ft_strlen(*var);
	len3 = ft_strlen(in->split_input[j]);
	last = ft_substr(in->split_input[j], len1 + len2 + 1, len3 - len2 - len1);
	if (!(ft_strncmp(*var, "?", 2)))
		expanded = ft_itoa(exit_status);
	else
		expanded = ft_getenv(*var, in);
	free(*var);
	if (!expanded)
		expanded = ft_strdup("");
	in->flags.count = len1 + ft_strlen(expanded);
	free(in->split_input[j]);
	in->split_input[j] = ft_strjoin3(*aux, expanded, last);
	free(*aux);
	free(expanded);
	free(last);
}

int		check_var(t_input *in)
{
	in->flags.i++;
	if(!ft_isalnum(in->split_input[in->flags.j][in->flags.i]))
	{
		if (in->split_input[in->flags.j][in->flags.i] == '\0')
		{
			in->flags.i--;
			return (2);
		}
		if (in->split_input[in->flags.j][in->flags.i] == '$')
		{
			if (ft_isalnum(in->split_input[in->flags.j][in->flags.i + 1])
				&& in->split_input[in->flags.j][in->flags.i + 1] != '\0')
				return (0);
			return (2);
		}
		if (in->flags.i > 1 && in->split_input[in->flags.j][in->flags.i] == '"'
			&& in->split_input[in->flags.j][in->flags.i - 2] == '"')
			return (2);
		if (in->split_input[in->flags.j][in->flags.i] == '"' && !in->flags.double_q)
			return (1);
		if (in->split_input[in->flags.j][in->flags.i] == '"' && in->flags.double_q)
			return (2);
		if (in->split_input[in->flags.j][in->flags.i] == '\'' && !in->flags.single_q
			&& !in->flags.double_q)
			return (1);
		if (in->split_input[in->flags.j][in->flags.i] == '?')
		{
			in->flags.i--;
			return (0);
		}
		if (in->split_input[in->flags.j][in->flags.i] == '_')
		{
			in->flags.i--;
			return (0);
		}
		else
			return(2);
	}
	in->flags.i--;
	return (0);
}

char	*get_var(char *str, int i)
{
	char *aux;
	int		j;

	j = i;
	if (str[i] == '?')
		return (aux = ft_strdup("?"));
	if (str[i] == '_')
		return (aux = ft_strdup("_"));
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	aux = ft_substr(str, j, i - j);
	return (aux);
}

void	expand_vars(t_input *in)
{
	char	*var;
	char 	*aux;
	int 	check;

	ft_bzero(&in->flags, sizeof(in->flags));
	while (in->split_input[in->flags.j] != NULL)
	{
		in->flags.i = 0;
		while (in->split_input[in->flags.j][in->flags.i] != '\0')
		{
			quotes_state(in, in->split_input[in->flags.j]);
			if (in->split_input[in->flags.j][in->flags.i] == '$' && !in->flags.single_q)
			{
				check = check_var(in);
				if (check == 1)
				{
					aux = del_str_pos(in->split_input[in->flags.j], in->flags.i - 1);
					free(in->split_input[in->flags.j]);
					in->split_input[in->flags.j] = ft_strdup(aux);
					free(aux);
				}
				else if (check == 0)
				{
					aux = ft_substr(in->split_input[in->flags.j], 0, in->flags.i);
					var = get_var(in->split_input[in->flags.j], in->flags.i + 1);
					insert_var(in, &var, &aux, in->flags.j);
					in->flags.i = in->flags.count - 1;
				}
			}
			in->flags.i++;
		}
		in->flags.j++;
	}
	in->split_input = quotes(in);
}
