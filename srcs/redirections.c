/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 03:03:21 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/28 13:41:27 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_redirs(t_input *in)
{
	int i;
	
	i = 0;
	in->is_infile = 0;
	in->is_outfile = 0;
	in->is_hdoc = 0;
	while(in->split_input[i])
	{
		if (!(ft_strncmp(in->split_input[i], "<<", 3)))
		{
			if (in->split_input[i + 1] != NULL)
				here_doc(in, i);
			else
				error_msg(in, ERR_SYNTAX, -1);
			i--;
		}
		i++;
	}
	i = 0;
	while (in->split_input[i])
	{
		if (!(ft_strncmp(in->split_input[i], "<", 2)))
		{
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
		if (in->split_input[i][0] == '>')
		{
			if (!(ft_strncmp(in->split_input[i], ">", 2)))
				in->fd_out = open(in->split_input[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
			if (!(ft_strncmp(in->split_input[i], ">>", 3)))
				in->fd_out = open(in->split_input[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0666);
			if (in->fd_out == -1)
				error_msg(in, ERR_PERM, i + 1);
			else
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
