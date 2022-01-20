/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:30:46 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/20 02:26:17 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	delete_head(t_input *in)
{
	t_list	*tmp;

	tmp = *in->env_list;
	*in->env_list = (*in->env_list)->next;
	ft_lstdelone(tmp, free);
}

void	unset_from_list(t_input *in, char **var, int size_var)
{
	t_list	*aux;
	t_list	*tmp;
	char	*str;

	aux = *in->env_list;
	str = (char *)aux->content;
	if (!(ft_strncmp((*var), str, size_var)) && str[size_var] == '=')
		delete_head(in);
	else
	{
		while (aux)
		{
			if (aux->next != NULL)
				str = (char *)aux->next->content;
			if (!(ft_strncmp((*var), str, size_var)) && str[size_var] == '=')
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

int	is_valid_id(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(ft_isalnum(str[i])) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	unset_aux2(t_input *in, char *var)
{
	int		size_var;

	size_var = ft_strlen(var);
	unset_from_list(in, &var, size_var);
	if (!(ft_strncmp(var, "PATH=", size_var)))
		in->path_unset = 1;
	free_matrix(in->dup_env);
	in->dup_env = list_to_matrix(*in->env_list);
}

void	unset(t_input *in, int j)
{
	char	*var;
	char	*tmp_env;

	if (in->split_in[1] == NULL)
		return ;
	while (in->split_in[j])
	{
		if (!is_valid_id(in->split_in[j]))
			error_msg(in, ERR_ID, j, 0);
		else
		{
			var = ft_strdup(in->split_in[j]);
			tmp_env = ft_getenv(var, in);
			if (tmp_env)
			{
				unset_aux2(in, var);
				free(tmp_env);
			}
			free(var);
		}
		j++;
	}
}
