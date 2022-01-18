/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:55:39 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/18 01:47:50 by ldurante         ###   ########.fr       */
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

void	check_quotes(t_input *in)
{
	if (in->user_in[in->f.i] == '"' && !in->f.single_q
		&& !in->f.double_q)
		in->f.double_q = 1;
	else if (in->user_in[in->f.i] == '"' && !in->f.single_q
		&& in->f.double_q)
		in->f.double_q = 0;
	else if (in->user_in[in->f.i] == '\'' && !in->f.single_q
		&& !in->f.double_q)
		in->f.single_q = 1;
	else if (in->user_in[in->f.i] == '\'' && in->f.single_q
		&& !in->f.double_q)
		in->f.single_q = 0;
}

int	check_errors2(t_input *in)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (in->user_in[i])
	{
		if (in->user_in[i] != ' ' && in->user_in[i] != '|')
			flag = 1;
		if (in->user_in[i] == '|' && flag == 0)
		{
			error_msg(in, ERR_SYNTAX, -1, 0);
			return (1);
		}
		i++;
	}
	return(0);
}

int	check_errors(t_input *in)
{
	char	c;
	int		count;
	int		flag_diff;
	int		special;

	special = 0;
	flag_diff = 0;
	while (in->user_in[in->f.i])
	{
		count = 0;
		check_quotes(in);
		if (in->f.double_q == 0 && in->f.single_q == 0)
		{
			if (in->user_in[in->f.i] == '<' || in->user_in[in->f.i] == '>'
				|| in->user_in[in->f.i] == '|' || char_space(in->user_in[in->f.i]))
			{
				if (in->user_in[in->f.i] == '<' || in->user_in[in->f.i] == '>'
					|| in->user_in[in->f.i] == '|')
				{
					if (in->user_in[in->f.i] == '|' && special == 1 && flag_diff == 0)
					{
						error_msg(in, ERR_SYNTAX, -2, 0);
						return (1);
					}
					else if (in->user_in[in->f.i] == '|')
					{
						count = 0;
						flag_diff = 0;
					}
					special = 1;
				}
				c = in->user_in[in->f.i];
				while (c == in->user_in[in->f.i] && count <= 2)
				{
					count++;
					in->f.i++;
				}
				while (char_space(in->user_in[in->f.i]))
					in->f.i++;
				if (((c == '<' || c == '>') && count > 2) || (c == '|' && count > 1)
					|| in->user_in[in->f.i] == c)
				{
					error_msg(in, ERR_SYNTAX, -2, 0);
					return (1);
				}
			}
			else
			{
				flag_diff = 1;
				in->f.i++;
			}
		}
		else
			in->f.i++;
	}
	if (flag_diff == 0 && special == 1)
	{
		error_msg(in, ERR_SYNTAX, -2, 0);
		return (1);
	}
	return (check_errors2(in));
}

void	read_in_aux(t_input *in)
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
			count_pipes(in);
			if (is_builtin(in) && !in->total_pipes && !in->is_hdoc)
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

int		is_space(char *str)
{
	int i;
	int c;

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

void	input_work(t_input *in, char **user)
{
	if (!is_space(in->user_in))
	{
		if (pair_quotes(in) == 0)
			read_in_aux(in);
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
		input_work(in, &user);
	else
	{
		write(2, "exit\n", 5);
		ft_lstclear(in->env_list, free);
		free(in->q_state);
		free(in->prompt);
		free(user);
		close(0);
		close(1);
		close(2);
		exit(0);
	}
}
