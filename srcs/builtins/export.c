/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:30:13 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/15 13:11:19 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Revisar leaks y longitud de funciones */

void	export(t_input *in)
{
	size_t	i;
	int		j;
	int		flag;
	int		size;
	char	*tmp;
	char	*env_value;
	char	**aux;

	i = 0;
	flag = 0;
	if (in->split_input[1] == NULL)
	{
		error_msg(in, ERR_ID, 2);
		return ;
	}
	j = 1;
	while (in->split_input[j])
	{		
		tmp = ft_strdup(in->split_input[j]);
		if (ft_strchr(in->split_input[j], '='))
			flag = 1;
		aux = ft_split(in->split_input[j], '=');
		if (aux)
		{
			while (aux[0][i] != '\0')
			{
				if (!(ft_isalnum(aux[0][i])))
				{
					error_msg(in, ERR_ID, 2);
					free_matrix(aux);
					free(tmp);
					return ;
				}
				else
				{
					if (flag && i == ft_strlen(aux[0]) - 1)
					{
						size = ft_strlen(tmp);
						env_value = ft_getenv(aux[0], in);
						if (env_value)
						{
							free(in->split_input[j]);
							in->split_input[j] = ft_strdup(aux[0]);
							unset(in, j);
							ft_lstadd_back(in->env_list,
								ft_new_node((void *) tmp, size + 1));
							free(env_value);
						}
						else
							ft_lstadd_back(in->env_list,
								ft_new_node((void *) tmp, size + 1));
						break ;
					}
				}
				i++;
			}
		}
		// free_matrix(aux);
		j++;
	}
	// free_matrix(aux);
	// free_matrix(in->split_input);
	free_matrix(in->dup_env);
	in->dup_env = list_to_matrix(*in->env_list);
}
