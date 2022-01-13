/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:30:46 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/13 15:15:07 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unset_aux(t_input *in, char *var, int size_var)
{
	t_list *aux;
	t_list *tmp;
	char	*str;

	aux = *in->env_list;
 	if (!(ft_strncmp(var, aux->content, size_var)))
		*in->env_list = (*in->env_list)->next;
	else
	{
		while (aux->next)
		{
			str = (char *)aux->next->content;
			if (!(ft_strncmp(var, str, size_var)) && str[size_var] == '=')
			{
				printf("%s\n", str);
				tmp = aux->next;
				aux->next = aux->next->next;
				ft_lstdelone(tmp, free);
				break ;
			}
			aux = aux->next;
		}
	}
}

int	valid_id2(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (!(ft_isalnum(str[i])) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	unset(t_input *in, int j)
{
	char	*var;
	int		size_var;
	char	*tmp_env;

	if (in->split_input[1] == NULL)
		return ;
	while (in->split_input[j])
	{
		if (!valid_id2(in->split_input[j]))
			error_msg(in, ERR_ID, j, 0);
		else
		{
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
		}
		j++;
	}
}
