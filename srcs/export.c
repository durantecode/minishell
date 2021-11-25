/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:30:13 by ldurante          #+#    #+#             */
/*   Updated: 2021/11/25 23:47:10 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	replace_env_var(t_input *in, char *s)
{
	int size_var;
	t_list *aux;
	// t_list *tmp;
	
	aux = *in->env_list;
	size_var = ft_strlen(s);
	while (aux)
	{
		if (!(ft_strncmp(s, aux->content, size_var)))
		{
			// tmp = aux->next;
			// aux->next = aux->next->next;
			// free(tmp);
			aux->content = in->split_input[1];
			break ;
		}
		aux = aux->next;
	}
	return(0);
}

void	export(t_input *in)
{
	int i;
	char **aux;
	int flag;
	int size;
	
	i = 0;
	flag = 0;
	if (in->split_input[1] == NULL)
	{
		printf("minishell: export: not a valid identifier\n");
		return ;
	}
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
				if (flag)
				{
					size = ft_strlen(in->split_input[1]);
					if (ft_getenv(aux[0], in))
						unset(in);
					else
						ft_lstadd_back(in->env_list, ft_new_node((void *) in->split_input[1], size + 1));
					return ;
				}
			}
			i++;	
		}
	}
}
