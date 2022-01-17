/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:30:13 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/13 17:30:30 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	valid_id(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (!(ft_isalnum(str[i])) && str[i] != '=' && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	export(t_input *in)
{
  	int		j;
	char	*env_value;
	char	**aux;
	char	*var;

	if (in->split_input[1] == NULL)
	{
		env(in, 1);
		return ;
	}
	j = 1;
	while (in->split_input[j])
	{
		if (ft_strlen(in->split_input[j]) != 0)
		{	
			aux = ft_split(in->split_input[j], '=');
			if (aux)
			{
				if (!valid_id(aux[0]))
					error_msg(in, ERR_ID, j, 0);
				else
				{		
					env_value = ft_getenv(aux[0], in);
					if (env_value)
					{
						var = ft_strdup(aux[0]);
						unset_aux(in, var, ft_strlen(var));
						ft_lstadd_back(in->env_list,
							ft_new_node((void *) in->split_input[j],
							ft_strlen(in->split_input[j]) + 1));
						free(env_value);
						free(var);
					}
					else
					{
						ft_lstadd_back(in->env_list,
							ft_new_node((void *) in->split_input[j],
							ft_strlen(in->split_input[j]) + 1));
					}
				}
			}
			free_matrix(aux);
		}
		else
			error_msg(in, ERR_ID2, -1, 0);
		j++;
	}
	free_matrix(in->dup_env);
	in->dup_env = list_to_matrix(*in->env_list);
}