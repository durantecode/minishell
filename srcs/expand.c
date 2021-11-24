/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 00:23:56 by ldurante          #+#    #+#             */
/*   Updated: 2021/11/24 22:22:29 by ldurante         ###   ########.fr       */
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
	char	*aux;


	aux = NULL;
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
}


void	expand_vars(t_input *in)
{
	int i;
	int j;
	int open_single;
	int	open_double;
	int front;
	char *var;
	char *first;

	i = 0;
	while (in->split_input[i] != NULL)
	{
		j = 0;
		front = 0;
		open_single = 0;
		open_double = 0;
		while (in->split_input[i][j] != '\0')
		{
			front = j;
			if (in->split_input[i][j] == '"' && !open_single)
			{
				if (!open_double)
					open_single += 2;
				else
					open_single++;
			}
			if (in->split_input[i][j] == '\'')
			{
				open_double++;
				if (!open_single)
					open_single++;
			}
			if (in->split_input[i][j] == '$' && open_single % 2 == 0)
			{
				j++;
				while (ft_isalnum(in->split_input[i][j]))
					j++;
				var = ft_substr(in->split_input[i], front + 1, j - 1 - front);
				first = ft_substr(in->split_input[i], 0, front);
				insert_var(in, var, first, i);

				free(var);
				free(first);
			}
			j++;
		}
		i++;
	}
}
