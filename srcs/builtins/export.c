/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:30:13 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/20 02:25:54 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	valid_id(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(ft_isalnum(str[i])) && str[i] != '=' && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	export_aux(t_input *in, char **aux, int j)
{
	char	*env_value;
	char	*var;

	if (!valid_id(aux[0]))
		error_msg(in, ERR_ID, j, 0);
	else
	{
		env_value = ft_getenv(aux[0], in);
		if (env_value)
		{
			var = ft_strdup(aux[0]);
			unset_from_list(in, &var, ft_strlen(var));
			ft_lstadd_back(in->env_list,
				ft_new_node((void *) in->split_in[j],
					ft_strlen(in->split_in[j]) + 1));
			free(env_value);
			free(var);
		}
		else
		{
			ft_lstadd_back(in->env_list,
				ft_new_node((void *) in->split_in[j],
					ft_strlen(in->split_in[j]) + 1));
		}
	}
}

void	export(t_input *in)
{
	char	**aux;
	int		j;

	if (in->split_in[1] == NULL)
	{
		env(in, 1);
		return ;
	}
	j = 1;
	while (in->split_in[j])
	{
		if (ft_strlen(in->split_in[j]) != 0)
		{	
			aux = ft_split(in->split_in[j], '=');
			if (aux)
				export_aux(in, aux, j);
			free_matrix(aux);
		}
		else
			error_msg(in, ERR_ID2, -1, 0);
		j++;
	}
	free_matrix(in->dup_env);
	in->dup_env = list_to_matrix(*in->env_list);
}
