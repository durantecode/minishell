/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:55:39 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/27 13:13:36 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*Hay que hacer que los errores vayan con la funcion de errores no con printf
en la misma funcion*/

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
	int		flag_diff;
	int		special;

	special = 0;
	flag_diff = 0;
	while (in->user_input[in->flags.i])
	{
		count = 0;
		check_errors_aux(in);
		if (in->user_input[in->flags.i] == '<' || in->user_input[in->flags.i] == '|'
			|| in->user_input[in->flags.i] == '>')
		{
			special = 1;
			if (in->flags.double_q == 0 && in->flags.single_q == 0)
				c = in->user_input[in->flags.i];
			else
				in->flags.i++;
			while ((in->user_input[in->flags.i] == c)
				&& count <= 2 && in->user_input[in->flags.i])
			{
				if (in->user_input[in->flags.i] == c)
					count++;
				in->flags.i++;
			}
			while (in->user_input[in->flags.i] == ' ' && in->user_input[in->flags.i])
				in->flags.i++;
			if (count > 2 || in->user_input[in->flags.i] == c)
			{

				printf("minishell: syntax error near unexpected token\n");
				return (1);
			}
		}
		else
		{
			if (in->user_input[in->flags.i] != ' ')
				flag_diff = 1;
			in->flags.i++;
		}
	}
	if ((special == 1 && flag_diff == 0))
	{
		printf("minishell: syntax error near unexpected token\n");
		return (1);
	}
	else
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
		if (check_args(in))
		{
			if (is_builtin(in) && count_pipes(in) == 1)
			{
				check_redirs(in);
				exec_args(in);
				if (in->is_outfile)
				{			
					dup2(in->back_stdout, STDOUT_FILENO);
					close(in->back_stdout);
				}
			}
			else
				init_arg_list(in);
			unlink(".hd_tmp");
		}
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
				error_msg(in, ERR_ARG, -1);
				add_history(in->user_input);
			}
		}
		// if (in->user_input[0] != '\0')
		// 	free_matrix(in->split_input);
		free(in->user_input);
		free(in->prompt);
		free(user);
	}
	else
	{
		// write(0, "exit\n", 5);
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


