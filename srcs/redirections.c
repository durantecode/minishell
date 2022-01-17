/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 03:03:21 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/17 22:03:38 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		infile(t_input *in, int i)
{
	in->fd_in = open(in->split_in[i + 1], O_RDONLY);
	if (in->fd_in == -1)
	{
		if (errno == EACCES)
			error_msg(in, ERR_PERM, i + 1, 0);
		else if (in->split_in[i + 1] == NULL)
			error_msg(in, ERR_SYNTAX, -1, 0);
		else
			error_msg(in, ERR_FILE, i + 1, 0);
		return (1);
	}
	else
	{
		remove_redir(in, i);
		if (!in->split_in[0])
			exit(0);
		if (!is_builtin(in) && !in->is_hdoc)
			dup2(in->fd_in, STDIN_FILENO);
		close(in->fd_in);
		in->is_infile = 1;
	}
	return (0);
}

void	outfile_aux(t_input *in, int i)
{
	remove_redir(in, i);
	if (!in->split_in[0])
		exit(0);
	if (!in->is_outfile)
		in->back_stdout = dup(STDOUT_FILENO);
	dup2(in->fd_out, STDOUT_FILENO);
	close(in->fd_out);
	in->is_outfile = 1;
}

int		outfile(t_input *in, int i)
{
	if (!(ft_strncmp(in->split_in[i], ">", 2)) && in->q_state[i] == 0)
		in->fd_out = open(in->split_in[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (!(ft_strncmp(in->split_in[i], ">>", 3)) && in->q_state[i] == 0)
		in->fd_out = open(in->split_in[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (in->fd_out == -1)
	{
		if (errno == EACCES)
			error_msg(in, ERR_PERM, i + 1, 0);
		else if (in->split_in[i + 1] == NULL)
			error_msg(in, ERR_SYNTAX, -1, 0);
		else
			error_msg(in, ERR_FILE, i + 1, 0);
		return (1);
	}
	if (in->fd_out > 2)
	{
		outfile_aux(in, i);
	}
	return (0);
}

void	check_redirs(t_input *in)
{
	int i;

	i = 0;
	in->is_infile = 0;
	in->is_outfile = 0;
	while (in->split_in[i])
	{
		if (!(ft_strncmp(in->split_in[i], "<", 2)) && in->q_state[i] == 0)
		{
			if (infile(in, i))
				return ;	
			i--;
		}
		i++;
	}
	i = 0;
	while (in->split_in[i])
	{
		if (!(ft_strncmp(in->split_in[i], ">", 1)) && in->q_state[i] == 0)
		{
			if (outfile(in, i))
				return ;	
			i--;
		}
		i++;
	}
}
