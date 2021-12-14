/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:30:46 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/14 02:44:56 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unset_aux(t_list *aux, char *var, int size_var)
{
	t_list	*tmp;

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

void	unset(t_input *in)
{
	char	*var;
	int		size_var;
	t_list	*aux;
	t_list	*tmp;
	int		j;

	aux = *in->env_list;
	if (in->split_input[1] == NULL)
	{
		error_msg(in, ERR_ID, 2);
		return ;
	}
	j = 1;
	while (in->split_input[j])
	{	
		var = ft_strjoin(in->split_input[j], "=");
		size_var = ft_strlen(var);
		if (!(ft_strncmp(var, aux->content, size_var)))
		{
			tmp = *in->env_list;
			*in->env_list = (*in->env_list)->next;
			free(tmp);
		}
		else
			unset_aux(aux, var, size_var);
		if (!(ft_strncmp(var, "PATH=", size_var)))
			in->path_unset = 1;
		j++;
		in->dup_env = list_to_matrix(*in->env_list);
	}
	// print_matrix(in->dup_env);
}
