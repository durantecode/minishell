/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:04:12 by ldurante          #+#    #+#             */
/*   Updated: 2021/11/30 01:12:53 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	count_pipes(t_input *in)
// {
// 	int	i;
// 	int	pipes;

// 	i = 0;
// 	pipes = 0;
// 	while (in->split_input[i] != NULL)
// 	{
// 		if (!(ft_strncmp(in->split_input[i], "|", 2)))
// 			pipes++;
// 		i++;
// 	}
// 	return (pipes);
// }

void	pipes(t_input *in)
{
	t_arg args[2];
	t_arg *aux;
	t_list *arg_list;
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	arg_list = NULL;
	// args = malloc(sizeof(t_arg));
	while (in->split_input[i] != NULL)
	{
		if (!(ft_strncmp(in->split_input[i], "|", 2)))
			break ;
		i++;
	}
	args[0].arg = malloc(sizeof(char *) * i + 1);
	args[1].arg = malloc(sizeof(char *) * i + 1);
	i = 0;
	while (in->split_input[i] != NULL)
	{
		if (!(ft_strncmp(in->split_input[i], "|", 2)))
		{
			args[k].arg[j] = NULL;
			ft_lstadd_back(&arg_list, ft_new_node((void *) &args[k], sizeof(t_arg)));
			i++;
			j = 0;
			k++;
		}
		args[k].arg[j] = ft_strdup(in->split_input[i]);
		i++;
		j++;
	}
	args[k].arg[i] = NULL;
	ft_lstadd_back(&arg_list, ft_new_node((void *) &args[k], sizeof(t_arg)));
	aux = (t_arg *)arg_list->content;
	print_matrix(aux->arg);
}
