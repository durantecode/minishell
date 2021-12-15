/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:30:13 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/15 16:42:33 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Revisar leaks y longitud de funciones */

int	good_value(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (!(ft_isalnum(str[i])) && str[i] != '=')
			return (0);
		i++;
	}
	return (1);
}

void	export(t_input *in)
{
  	int		j;
	int		flag;
	char	*env_value;
	char	**aux;
	char	*var;
	flag = 0;
	if (in->split_input[1] == NULL)
	{
		error_msg(in, ERR_ID, 2);
		return ;
	}
	j = 1;
	while (in->split_input[j])
	{
		if (ft_strchr(in->split_input[j], '='))
			flag = 1;
		aux = ft_split(in->split_input[j], '=');
		if (aux)
		{
			if (!good_value(aux[0]))
			{
				error_msg(in, ERR_ID, 2);
				free(aux);
				return;
			}
			env_value = ft_getenv(aux[0], in);
			if (env_value)
			{
				var = ft_strjoin(aux[0], "=");
				unset_aux(*in->env_list, var, ft_strlen(var));
				ft_lstadd_back(in->env_list,
					ft_new_node((void *) in->split_input[j],
					ft_strlen(in->split_input[j]) + 1));
				free(env_value);
				free(var);
			}
			else if (aux[1])
				ft_lstadd_back(in->env_list,
					ft_new_node((void *) in->split_input[j],
					ft_strlen(in->split_input[j]) + 1));
		}
		free_matrix(aux);
		j++;
	}
	free_matrix(in->dup_env);
	in->dup_env = list_to_matrix(*in->env_list);
}