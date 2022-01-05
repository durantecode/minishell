/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 03:03:21 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/05 17:15:19 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void handler3(int code)
{
	if (code == SIGINT)
	{
		exit(130);
	}
	if (code == SIGQUIT)
	{
		exit(130);
	}
}

void	check_redirs(t_input *in)
{
	int i;

	i = 0;
	in->is_infile = 0;
	in->is_outfile = 0;
	in->is_hdoc = 0;
	while(in->split_input[i])
	{
		if (!(ft_strncmp(in->split_input[i], "<<", 3)) && in->quote_state[i] == 0)
		{
			if (in->split_input[i + 1] != NULL)
			{
				signal(SIGINT, handler3);
				signal(SIGQUIT, handler3);
				here_doc(in, i);
			}
			else
				error_msg(in, ERR_SYNTAX, -1);
		}
		i++;
	}
	i = 0;
	while (in->split_input[i])
	{
		if (!(ft_strncmp(in->split_input[i], "<", 2)) && in->quote_state[i] == 0)
		{
			if (in->split_input[i + 1] == NULL)
			{
				error_msg(in, ERR_SYNTAX, -1);
				return ;
			}
			in->fd_in = open(in->split_input[i + 1], O_RDONLY);
			if (in->fd_in == -1)
				error_msg(in, ERR_FILE, i + 1);
			else
			{
				remove_redir(in, i);
				if (!(ft_strncmp(in->split_input[0], "", 2)))
					exit(0);
				if (!is_builtin(in) && !in->is_hdoc)
					dup2(in->fd_in, STDIN_FILENO);
				close(in->fd_in);
				in->is_infile = 1;
				i--;
			}
		}
		i++;
	}
	i = 0;
	while (in->split_input[i])
	{
		if (!(ft_strncmp(in->split_input[i], ">", 2)) && in->quote_state[i] == 0)
		{
			if (in->split_input[i + 1] == NULL)
			{
				error_msg(in, ERR_SYNTAX, -1);
				return ;
			}
			in->fd_out = open(in->split_input[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
			if (in->fd_out == -1)
				error_msg(in, ERR_PERM, i + 1);
			if (in->fd_out > 2)
			{
				remove_redir(in, i);
				if (!(ft_strncmp(in->split_input[0], "", 2)))
					exit(0);
				if (!in->is_outfile)
					in->back_stdout = dup(STDOUT_FILENO);
				dup2(in->fd_out, STDOUT_FILENO);
				close(in->fd_out);
				in->is_outfile = 1;
				i--;
			}
		}
		else if (!(ft_strncmp(in->split_input[i], ">>", 3)) && in->quote_state[i] == 0)
		{
			if (in->split_input[i + 1] == NULL)
			{
				error_msg(in, ERR_SYNTAX, -1);
				return ;
			}
			in->fd_out = open(in->split_input[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0666);
			if (in->fd_out == -1)
				error_msg(in, ERR_PERM, i + 1);
			if (in->fd_out > 2)
			{
				remove_redir(in, i);
				if (!(ft_strncmp(in->split_input[0], "", 2)))
					exit(0);
				if (!in->is_outfile)
					in->back_stdout = dup(STDOUT_FILENO);
				dup2(in->fd_out, STDOUT_FILENO);
				close(in->fd_out);
				in->is_outfile = 1;
				i--;
			}
		}
		i++;
	}
}
