/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 00:23:56 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/18 17:30:02 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	insert_var(t_input *in, char **var, char **aux, int j)
{
	int		len1;
	int		len2;
	int		len3;
	char	*last;
	char	*expanded;

	len1 = ft_strlen(*aux);
	len2 = ft_strlen(*var);
	len3 = ft_strlen(in->split_in[j]);
	last = ft_substr(in->split_in[j], len1 + len2 + 1, len3 - len2 - len1);
	if (!(ft_strncmp(*var, "?", 2)))
		expanded = ft_itoa(g_exit_status);
	else if (j > 0 && !(ft_strncmp(in->split_in[j - 1], "<<", 3)))
		expanded = ft_strdup(in->split_in[j]);
	else
		expanded = ft_getenv(*var, in);
	free(*var);
	if (!expanded)
		expanded = ft_strdup("");
	in->f.count = len1 + ft_strlen(expanded);
	free(in->split_in[j]);
	in->split_in[j] = ft_strjoin3(*aux, expanded, last);
	free(*aux);
	free(expanded);
	free(last);
}

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

char	*get_var(char *str, int i)
{
	char	*aux;
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
		var = get_var(in->split_in[in->f.j], in->f.i + 1);
		insert_var(in, &var, &aux, in->f.j);
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
			// printf("%d : %c\n", in->f.single_q, in->split_in[in->f.j][in->f.i]);
			if (in->split_in[in->f.j][in->f.i] == '$' && !in->f.single_q)
				expand_vars_aux(in);
			in->f.i++;
		}
		in->f.j++;
	}
	in->split_in = quotes(in);
}
