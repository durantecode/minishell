/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 03:03:21 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/13 11:56:50 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_hdoc(t_input *in)
{
	int i;

	i = 0;
	in->is_hdoc = 0;
	while(in->split_input[i])
	{
		if (!(ft_strncmp(in->split_input[i], "<<", 3)) && in->quote_state[i] == 0)
		{
			if (in->split_input[i + 1] != NULL)
				in->is_hdoc = 1;
		}
		i++;
	}
}

void	find_hdoc(t_input *in)
{
	int	i;

	i = 0;
	in->is_hdoc = 0;
	while(in->split_input[i])
	{
		if (!(ft_strncmp(in->split_input[i], "<<", 3)) && in->quote_state[i] == 0)
		{
			if (in->split_input[i + 1] != NULL)
			{
				if (!is_builtin(in))
				{	
					signal(SIGINT, handler4);
					signal(SIGQUIT, handler3);
				}
				else
					signal(SIGINT, SIG_IGN);
				here_doc(in, i);
				i--;
			}
			else
				error_msg(in, ERR_SYNTAX, -1, 0);
		}
		i++;
	}
}

void	check_redirs(t_input *in)
{
	int i;

	i = 0;
	in->is_infile = 0;
	in->is_outfile = 0;
	while (in->split_input[i])
	{
		if (!(ft_strncmp(in->split_input[i], "<", 2)) && in->quote_state[i] == 0)
		{
			in->fd_in = open(in->split_input[i + 1], O_RDONLY);
			if (in->fd_in == -1)
				error_msg(in, ERR_FILE, i + 1, 0);
			else
			{
				remove_redir(in, i);
				if (!in->split_input[0])
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
			in->fd_out = open(in->split_input[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
			if (in->fd_out == -1)
				error_msg(in, ERR_PERM, i + 1, 0);
			if (in->fd_out > 2)
			{
				remove_redir(in, i);
				if (!in->split_input[0])
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
			in->fd_out = open(in->split_input[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0666);
			if (in->fd_out == -1)
				error_msg(in, ERR_PERM, i + 1, 0);
			if (in->fd_out > 2)
			{
				remove_redir(in, i);
				if (!in->split_input[0])
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
