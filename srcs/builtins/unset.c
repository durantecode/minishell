/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:30:46 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/15 16:18:40 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unset_aux(t_list *aux, char *var, int size_var)
{
	t_list *tmp;

	while (aux)
	{
		if (!(ft_strncmp(var, aux->next->content, size_var)))
		{
			tmp = aux->next;
			aux->next = aux->next->next;
			// free(tmp);
			ft_lstdelone(tmp, free);
			break ;
		}
		aux = aux->next;
	}
}

void	unset(t_input *in, int j)
{
	char	*var;
	int		size_var;
	t_list	*aux;
	t_list	*tmp;

	aux = *in->env_list;
	if (in->split_input[1] == NULL)
	{
		error_msg(in, ERR_ID, 2);
		return ;
	}
	while (in->split_input[j])
	{
		//var = ft_strjoin(in->split_input[j], "=");
		var = ft_strdup(in->split_input[j]);
		size_var = ft_strlen(var);
		if (!(ft_strncmp(var, aux->content, size_var)))
		{
			tmp = *in->env_list;
			*in->env_list = (*in->env_list)->next;
			// ft_lstclear(&tmp, free); ---> REVISAR LEAKS
		}
		else
			unset_aux(aux, var, size_var);
		if (!(ft_strncmp(var, "PATH=", size_var)))
			in->path_unset = 1;
		j++;
		free(var);
		free_matrix(in->dup_env);
		in->dup_env = list_to_matrix(*in->env_list);
	}
	// print_matrix(in->dup_env);
}
