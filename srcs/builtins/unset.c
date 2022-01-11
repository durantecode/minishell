/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:30:46 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/10 13:05:51 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unset_aux(t_input *in, char *var, int size_var)
{
	t_list *aux;
	t_list *tmp;

	aux = *in->env_list;
 	if (!(ft_strncmp(var, aux->content, size_var)))
		*in->env_list = (*in->env_list)->next;
	else
	{
		while (aux)
		{
			if (!(ft_strncmp(var, aux->next->content, size_var)))
			{
				tmp = aux->next;
				aux->next = aux->next->next;
				ft_lstdelone(tmp, free);
				break ;
			}
			aux = aux->next;
		}
	}
}

void	unset(t_input *in, int j)
{
	char	*var;
	int		size_var;
	// t_list	*aux;
	char	*tmp_env;

	if (in->split_input[1] == NULL)
	{
		error_msg(in, ERR_ID, -1);
		return ;
	}
	while (in->split_input[j])
	{
		// aux = *in->env_list;
		var = ft_strdup(in->split_input[j]);
		tmp_env = ft_getenv(var, in);
		if (tmp_env)
		{
			size_var = ft_strlen(var);
			unset_aux(in, var, size_var);
			if (!(ft_strncmp(var, "PATH=", size_var)))
				in->path_unset = 1;
			free_matrix(in->dup_env);
			in->dup_env = list_to_matrix(*in->env_list);
			free(tmp_env);
		}
		free(var);
		j++;
	}
}
