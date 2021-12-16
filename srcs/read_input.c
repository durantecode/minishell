/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:55:39 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/16 13:32:56 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	ft_lstclear2(t_list **lst)
// {
// 	t_list	*copy;

// 	copy = NULL;
// 	if (lst)
// 	{
// 		while (*lst)
// 		{
// 			copy = (*lst)->next;
// 			ft_lstdelone(*lst, free);
// 			*lst = copy;
// 		}
// 	}
// }

int	pair_quotes(t_input *in)
{
	ft_bzero(&in->flags, sizeof(in->flags));
	while (in->user_input[in->flags.i])
	{
		if (in->user_input[in->flags.i] == '"' && !in->flags.single_q
			&& !in->flags.double_q)
		{
			in->flags.count_double++;
			in->flags.double_q = 1;
		}
		else if (in->user_input[in->flags.i] == '"' && !in->flags.single_q
			&& in->flags.double_q && (in->flags.count_double++))
			in->flags.double_q = 0;
		else if (in->user_input[in->flags.i] == '\'' && !in->flags.single_q
			&& !in->flags.double_q)
		{
			in->flags.count++;
			in->flags.single_q = 1;
		}
		else if (in->user_input[in->flags.i] == '\'' && in->flags.single_q
			&& !in->flags.double_q && (in->flags.count++))
			in->flags.single_q = 0;
		in->flags.i++;
	}
	return (in->flags.count_double % 2 + in->flags.count % 2);
}

void	check_errors_aux(t_input *in)
{
	if (in->user_input[in->flags.i] == '"' && !in->flags.single_q
		&& in->flags.double_q)
		in->flags.double_q = 1;
	else if (in->user_input[in->flags.i] == '"' && !in->flags.single_q
		&& in->flags.double_q)
		in->flags.double_q = 0;
	else if (in->user_input[in->flags.i] == '\'' && !in->flags.single_q
		&& !in->flags.double_q)
		in->flags.single_q = 1;
	else if (in->user_input[in->flags.i] == '\'' && in->flags.single_q
		&& !in->flags.double_q)
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
				&& count <= 2 && in->user_input[in->flags.i])
			{
				if (in->user_input[in->flags.i] == c)
					count++;
				in->flags.i++;
			}
			if (count > 2)
				printf("minishell: syntax error near '%c'\n", c);
			if (count > 2)
				return (1);
		}
		else
			in->flags.i++;
	}
	return (0);
}

void	read_input_aux(t_input *in, char *aux)
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
		check_redirs(in);
		// print_matrix(in->split_input);
		// print_matrix(in->dup_env);
		if (is_builtin(in) && count_pipes(in) == 1)
			exec_args(in);
		else
			init_arg_list(in);
	}
}

void	read_input(t_input *in)
{
	char	*user;
	char	*aux;

	aux = NULL;
	user = ft_getenv("USER", in);
	if (!user)
		user = ft_strdup("guest");
	in->prompt = ft_strjoin(user, "@minishell> $ ");
	in->user_input = readline(in->prompt);
	if (in->user_input)
	{
		if ((ft_strncmp(in->user_input, "", 1)))
		{
			if (pair_quotes(in) == 0)
				read_input_aux(in, aux);
			else
			{
				error_msg(in, ERR_ARG, 2);
				add_history(in->user_input);
			}
		}
		if (in->user_input[0] != '\0')
			free_matrix(in->split_input);
		free(in->user_input);
		free(in->prompt);
		free(user);
	}
	else
	{
		printf("exit\n");
		// free_matrix(in->dup_env);
		// free_matrix(in->old_environ);
		//free_matrix(in->split_input);
		ft_lstclear(in->env_list, free);
		free(in->prompt);
		free(user);
		exit(0);
	}
}


