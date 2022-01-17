/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:55:39 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/15 18:03:56 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	check_quotes(t_input *in)
{
	if (in->user_input[in->flags.i] == '"' && !in->flags.single_q
		&& !in->flags.double_q)
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

int	check_errors2(t_input *in)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (in->user_input[i])
	{
		if (in->user_input[i] != ' ' && in->user_input[i] != '|')
			flag = 1;
		if (in->user_input[i] == '|' && flag == 0)
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
	while (in->user_input[in->flags.i])
	{
		count = 0;
		check_quotes(in);
		if (in->flags.double_q == 0 && in->flags.single_q == 0)
		{
			if (in->user_input[in->flags.i] == '<' || in->user_input[in->flags.i] == '>'
				|| in->user_input[in->flags.i] == '|' || char_space(in->user_input[in->flags.i]))
			{
				if (in->user_input[in->flags.i] == '<' || in->user_input[in->flags.i] == '>'
					|| in->user_input[in->flags.i] == '|')
				{
					if (in->user_input[in->flags.i] == '|' && special == 1 && flag_diff == 0)
					{
						error_msg(in, ERR_SYNTAX, -2, 0);
						return (1);
					}
					else if (in->user_input[in->flags.i] == '|')
					{
						count = 0;
						flag_diff = 0;
					}
					special = 1;
				}
				c = in->user_input[in->flags.i];
				while (c == in->user_input[in->flags.i] && count <= 2)
				{
					count++;
					in->flags.i++;
				}
				while (char_space(in->user_input[in->flags.i]))
					in->flags.i++;
				if (((c == '<' || c == '>') && count > 2) || (c == '|' && count > 1)
					|| in->user_input[in->flags.i] == c)
				{
					error_msg(in, ERR_SYNTAX, -2, 0);
					return (1);
				}
			}
			else
			{
				flag_diff = 1;
				in->flags.i++;
			}
		}
		else
			in->flags.i++;
	}
	if (flag_diff == 0 && special == 1)
	{
		error_msg(in, ERR_SYNTAX, -2, 0);
		return (1);
	}
	return (check_errors2(in));
}

void	read_input_aux(t_input *in)
{
	if (in->user_input[0] != '\0')
		add_history(in->user_input);
	ft_bzero(&in->flags, sizeof(in->flags));
	if (!check_errors(in))
	{
		split_pipes(in);
		if (check_args(in))
		{
			check_hdoc(in);
			if (is_builtin(in) && count_pipes(in) == 0 && !in->is_hdoc)
			{
				// exec_hdoc(in);
				check_redirs(in);
				if (!in->is_err)
					exec_args(in);
				if (in->is_outfile)
				{
					dup2(in->back_stdout, STDOUT_FILENO);
					close(in->back_stdout);
				}
				if (!in->is_err)
					exit_status = 0;
			}
			else
				init_arg_list(in);
		}
	}
}

int		char_space(char c)
{
	if (c != '\t' && c != ' ' && c != '\n'
	&& c != '\f' && c != '\v' && c != '\r')
		return (0);
	return (1);
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

void	read_input(t_input *in)
{
	char	*user;

	user = ft_getenv("USER", in);
	if (!user)
		user = ft_strdup("guest");
	in->prompt = ft_strjoin(user, "@minishell> $ ");
	in->user_input = readline(in->prompt);
	in->is_err = 0;
	in->quote_state = malloc(1);
	if (in->user_input)
	{
		if (!is_space(in->user_input))
		{
			if (pair_quotes(in) == 0)
				read_input_aux(in);
			else
			{
				error_msg(in, ERR_ARG, -2, 0);
				add_history(in->user_input);
			}
		}
		if (in->split_input)
		{	
			free_matrix(in->split_input);
			in->split_input = NULL;
		}
		free(in->quote_state);
		free(in->user_input);
		free(in->prompt);
		free(user);
	}
	else
	{
		close(0);
		close(1);
		close(2);
		free(in->quote_state);
		write(2, "exit\n", 5);
		ft_lstclear(in->env_list, free);
		free(in->prompt);
		free(user);
		exit(0);
	}
}


