/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:55:39 by ldurante          #+#    #+#             */
/*   Updated: 2021/11/25 16:16:30 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pair_quotes(t_input *in)
{
	ft_bzero(&in->flags, sizeof(in->flags));
	while (in->user_input[in->flags.i])
	{
		if (in->user_input[in->flags.i] == '"' && in->flags.single_q == 0 && in->flags.double_q == 0)
		{
			in->flags.count_double++;
			in->flags.double_q = 1;
		}
		else if (in->user_input[in->flags.i] == '"' && in->flags.single_q == 0 && in->flags.double_q == 1)
		{
			in->flags.count_double++;
			in->flags.double_q = 0;
		}
		else if (in->user_input[in->flags.i] == '\'' && in->flags.single_q == 0 && in->flags.double_q == 0)
		{
			in->flags.count++;
			in->flags.single_q = 1;
		}
		else if (in->user_input[in->flags.i] == '\'' && in->flags.single_q == 1 && in->flags.double_q == 0)
		{
			in->flags.count++;
			in->flags.single_q = 0;
		}
		in->flags.i++;
	}
	return (in->flags.count_double % 2 == 0 + in->flags.count % 2 == 0);
}

void	read_input(t_input *in)
{
	char	*prompt;
	char	*user;
	char	*aux;

	user = ft_getenv("USER", in);
	if (!user)
		user = ft_strdup("guest");
	prompt = ft_strjoin(user, "@minishell> $ ");
	in->user_input = readline(prompt);
	if (pair_quotes(in) == 0)
	{
		if (in->user_input[0] != '\0')
			add_history(in->user_input);
		aux = in->user_input;
		in->user_input = split_pipes(in);
		free(aux);
		check_args(in);
		if (in->split_input[0] != NULL)
			builtins(in);
		free(user);
	}
	else
	{
		printf("minishell: Invalid argument\n");
		if (in->user_input[0] != '\0')
			add_history(in->user_input);
	}
	free(prompt);
}
