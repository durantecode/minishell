/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:30:13 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/01 11:17:19 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	export(t_input *in)
{
	size_t	i;
	int		flag;
	int		size;
	char	*tmp;
	char	**aux;

	i = 0;
	flag = 0;
	if (in->split_input[1] == NULL)
	{
		printf("minishell: export: not a valid identifier\n");
		return ;
	}
	tmp = ft_strdup(in->split_input[1]);
	if (ft_strchr(in->split_input[1], '='))
		flag = 1;
	aux = ft_split(in->split_input[1], '=');
	if (aux)
	{
		while (aux[0][i] != '\0')
		{
			if (!(ft_isalnum(aux[0][i])))
			{
				printf("minishell: export: not a valid identifier\n");
				return ;
			}
			else
			{
				if (flag && i == ft_strlen(aux[0]) - 1)
				{
					size = ft_strlen(tmp);
					if (ft_getenv(aux[0], in))
					{
						in->split_input[1] = ft_strdup(aux[0]);
						unset(in);
						ft_lstadd_back(in->env_list, ft_new_node((void *) tmp, size + 1));
					}
					else
						ft_lstadd_back(in->env_list, ft_new_node((void *) tmp, size + 1));
					return ;
				}
			}
			i++;
		}
	}
}
