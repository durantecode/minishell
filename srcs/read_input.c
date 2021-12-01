/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:55:39 by ldurante          #+#    #+#             */
/*   Updated: 2021/11/30 17:24:01 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pair_quotes(t_input *in)
{
	ft_bzero(&in->flags, sizeof(in->flags));
	while (in->user_input[in->flags.i])
	{
		if (in->user_input[in->flags.i] == '"' && in->flags.single_q == 0
			&& in->flags.double_q && (in->flags.count_double++) == 0)
			in->flags.double_q = 1;
		else if (in->user_input[in->flags.i] == '"' && in->flags.single_q == 0
			&& in->flags.double_q && (in->flags.count_double++) == 1)
			in->flags.double_q = 0;
		else if (in->user_input[in->flags.i] == '\'' && in->flags.single_q == 0
			&& in->flags.double_q && (in->flags.count++) == 0)
			in->flags.single_q = 1;
		else if (in->user_input[in->flags.i] == '\'' && in->flags.single_q == 1
			&& in->flags.double_q && (in->flags.count++) == 0)
			in->flags.single_q = 0;
		in->flags.i++;
	}
	return (in->flags.count_double % 2 + in->flags.count % 2);
}

void	check_errors_aux(t_input *in)
{
	if (in->user_input[in->flags.i] == '"' && in->flags.single_q == 0
		&& in->flags.double_q && (in->flags.count_double++) == 0)
		in->flags.double_q = 1;
	else if (in->user_input[in->flags.i] == '"' && in->flags.single_q == 0
		&& in->flags.double_q && (in->flags.count_double++) == 1)
		in->flags.double_q = 0;
	else if (in->user_input[in->flags.i] == '\'' && in->flags.single_q == 0
		&& in->flags.double_q && (in->flags.count++) == 0)
		in->flags.single_q = 1;
	else if (in->user_input[in->flags.i] == '\'' && in->flags.single_q == 1
		&& in->flags.double_q && (in->flags.count++) == 0)
		in->flags.single_q = 0;
}

int	check_errors(t_input *in)
{
	char	c;
	int		count;

	while (in->user_input[in->flags.i])
	{
		count = 0;
		check_errors_aux(in);
		if (in->user_input[in->flags.i] == '<' || in->user_input[in->flags.i] == '|'
			|| in->user_input[in->flags.i] == '>')
		{
			if (in->flags.double_q == 0 && in->flags.single_q == 0)
				c = in->user_input[in->flags.i];
			else
				in->flags.i++;
			while ((in->user_input[in->flags.i] == c || in->user_input[in->flags.i] == ' ')
				&& count <=2 && in->user_input[in->flags.i])
			{
				if (in->user_input[in->flags.i] == c)
					count++;
				in->flags.i++;
			}
			if (count > 2)
				printf("minishel: syntax error near '%c'\n", c);
			if (count > 2)
				return (1);
		}
		else 
			in->flags.i++;
	}
	return (0);
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
		ft_bzero(&in->flags, sizeof(in->flags));
		if (!check_errors(in))
		{
			aux = in->user_input;
			in->user_input = split_pipes(in);
			free(aux);
			check_args(in);
			print_matrix(in->split_input);
			if (in->split_input[0] != NULL)
			 	builtins(in);
			//init_arg_list(in);
		}
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
