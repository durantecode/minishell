/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:30:46 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/08 18:17:00 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	unset(t_input *in)
{
	char	*var;
	int		size_var;
	t_list	*aux;
	t_list	*tmp;

	aux = *in->env_list;
	if (in->split_input[1] == NULL)
	{
		printf("minishell: unset: not a valid identifier\n");
		return ;
	}
	var = ft_strjoin(in->split_input[1], "=");
	size_var = ft_strlen(var);
	if (!(ft_strncmp(var, aux->content, size_var)))
	{
		tmp = *in->env_list;
		*in->env_list = (*in->env_list)->next;
		free(tmp);
	}
	else
	{
		while (aux)
		{
			if (!(ft_strncmp(var, aux->next->content, size_var)))
			{
				tmp = aux->next;
				aux->next = aux->next->next;
				free(tmp);
				break ;
			}
			aux = aux->next;
		}
	}
	if (!(ft_strncmp(var, "PATH=", size_var)))
		in->path_unset = 1;
	list_to_matrix(in);
}
