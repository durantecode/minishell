/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:04:12 by ldurante          #+#    #+#             */
/*   Updated: 2021/11/29 20:38:46 by ldurante         ###   ########.fr       */
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
	t_arg *args;
	t_list *arg_list;
	t_arg *aux;
	int i;

	i = 0;
	arg_list = NULL;
	args = malloc(sizeof(t_arg));
	while (in->split_input[i] != NULL)
	{
		if (!(ft_strncmp(in->split_input[i], "|", 2)))
			break ;
		i++;
	}
	args->arg = malloc(sizeof(char *) * i + 1);
	i = 0;
	while (in->split_input[i] != NULL)
	{
		if (!(ft_strncmp(in->split_input[i], "|", 2)))
			break ;
		args->arg[i] = ft_strdup(in->split_input[i]);
		i++;
	}
	args->arg[i] = NULL;
	ft_lstadd_back(&arg_list, ft_new_node((void *) args, sizeof(t_arg)));
	aux = (t_arg *)arg_list->content;
	print_matrix(aux->arg);
	// printf("AA: %s\n", aux->arg[0]);
}
