/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:55:39 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/17 12:40:48 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pair_quotes(t_input *in)
{
	ft_bzero(&in->f, sizeof(in->f));
	while (in->user_in[in->f.i])
	{
		if (in->user_in[in->f.i] == '"' && !in->f.single_q
			&& !in->f.double_q)
		{
			in->f.count_double++;
			in->f.double_q = 1;
		}
		else if (in->user_in[in->f.i] == '"' && !in->f.single_q
			&& in->f.double_q && (in->f.count_double++))
			in->f.double_q = 0;
		else if (in->user_in[in->f.i] == '\'' && !in->f.single_q
			&& !in->f.double_q)
		{
			in->f.count++;
			in->f.single_q = 1;
		}
		else if (in->user_in[in->f.i] == '\'' && in->f.single_q
			&& !in->f.double_q && (in->f.count++))
			in->f.single_q = 0;
		in->f.i++;
	}
	return (in->f.count_double % 2 + in->f.count % 2);
}

int	is_space(char *str)
{
	int	i;
	int	c;

	i = 0;
	while (str[i])
	{
		c = str[i];
		if (c != '\t' && c != ' ' && c != '\n'
			&& c != '\f' && c != '\v' && c != '\r')
			return (0);
		i++;
	}
	return (1);
}

void	read_input_aux(t_input *in)
{
	if (in->user_in[0] != '\0')
		add_history(in->user_in);
	ft_bzero(&in->f, sizeof(in->f));
	if (!check_errors(in))
	{
		split_args(in);
		if (check_args(in))
		{
			check_hdoc(in);
			if (is_builtin(in) && count_pipes(in) == 0 && !in->is_hdoc)
			{
				check_redirs(in);
				if (!in->is_err)
					exec_args(in);
				if (in->is_outfile)
					dup2(in->back_stdout, STDOUT_FILENO);
				if (in->is_outfile)
					close(in->back_stdout);
				if (!in->is_err)
					g_exit_status = 0;
			}
			else
				init_arg_list(in);
		}
	}
}

void	input_action(t_input *in, char **user)
{
	if (!is_space(in->user_in))
	{
		if (pair_quotes(in) == 0)
			read_input_aux(in);
		else
		{
			error_msg(in, ERR_ARG, -2, 0);
			add_history(in->user_in);
		}
	}
	if (in->split_in)
	{	
		free_matrix(in->split_in);
		in->split_in = NULL;
	}
	free(in->q_state);
	free(in->user_in);
	free(in->prompt);
	free(*user);
}

void	read_input(t_input *in)
{
	char	*user;

	user = ft_getenv("USER", in);
	if (!user)
		user = ft_strdup("guest");
	in->prompt = ft_strjoin(user, "@minishell> $ ");
	in->user_in = readline(in->prompt);
	in->is_err = 0;
	in->q_state = malloc(1);
	if (in->user_in)
		input_action(in, &user);
	else
	{
		write(2, "exit\n", 5);
		free(in->q_state);
		ft_lstclear(in->env_list, free);
		free(in->prompt);
		free(user);
		close(0);
		close(1);
		close(2);
		exit(0);
	}
}
