/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 00:23:56 by ldurante          #+#    #+#             */
/*   Updated: 2021/11/24 17:53:16 by dpavon-g         ###   ########.fr       */
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
}

void	expand_vars(t_input *in)
{
	int		i;
	int		j;
	int		front;
	char	*var;
	char	*first;

	i = 0;
	while (in->split_input[i] != NULL && in->expand[i] == 0)
	{
		j = 0;
		front = 0;
		while (in->split_input[i][j] != '\0')
		{
			if (in->split_input[i][j] == '$')
			{
				j++;
				while (ft_isalnum(in->split_input[i][j]))
					j++;
				var = ft_substr(in->split_input[i], front + 1, j - 1 - front);
				first = ft_substr(in->split_input[i], 0, front);
				insert_var(in, var, first, i);
			}
			j++;
			front++;
		}
		i++;
	}
}
