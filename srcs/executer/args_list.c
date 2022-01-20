/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 10:13:09 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/20 10:29:38 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_pipes(t_input *in)
{
	int	i;

	i = 0;
	in->total_pipes = 0;
	while (in->split_in[i] != NULL)
	{
		if (!(ft_strncmp(in->split_in[i], "|", 2)) && in->q_state[i] == 0)
			in->total_pipes++;
		i++;
	}
	return (in->total_pipes);
}

void	init_arg_list_aux(t_input *in, t_list **arg_list, int i[4])
{
	t_arg	*args;

	args = malloc(sizeof(t_arg));
	args->arg = malloc(sizeof(char *) * (i[2] + 1));
	args->quotes = malloc(sizeof(int) * (i[2]));
	i[0] = i[0] - i[2];
	while (in->split_in[i[0]] != NULL
		&& ((ft_strncmp(in->split_in[i[0]], "|", 2))
			|| in->q_state[i[0]] == 1))
	{
		args->arg[i[3]] = ft_strdup(in->split_in[i[0]]);
		if (in->q_state[i[0]] == 1)
			args->quotes[i[3]] = 1;
		else
			args->quotes[i[3]] = 0;
		i[0]++;
		i[3]++;
	}
	args->arg[i[3]] = NULL;
	ft_lstadd_back(arg_list, ft_lstnew((void *) args));
}

void	init_arg_list(t_input *in)
{
	t_list	*arg_list;
	int		i[4];

	i[0] = 0;
	i[1] = 0;
	arg_list = NULL;
	while (i[1] <= in->total_pipes)
	{
		i[3] = 0;
		i[2] = 0;
		while (in->split_in[i[0]] != NULL
			&& ((ft_strncmp(in->split_in[i[0]], "|", 2))
				|| in->q_state[i[0]] == 1))
		{
			i[0]++;
			i[2]++;
		}
		init_arg_list_aux(in, &arg_list, i);
		i[1]++;
		i[0]++;
	}
	free(in->q_state);
	free_matrix(in->split_in);
	pipex(in, arg_list);
}
