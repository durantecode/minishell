/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 03:03:21 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/26 15:34:38 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


// in->fd_in = open(".tmp", O_CREAT | O_WRONLY | O_APPEND, 0666);

char	**remove_redir(t_input *in, int i)
{
	int j;

	j = i;
	i += 2;
	if (in->split_input[i] == NULL && in->split_input[0][0] == '<')
	{
		in->split_input[0] = ft_strdup("");
		in->split_input[1] = NULL;
		
	}
	else
	{
		while(in->split_input[i])
		{
			in->split_input[j] = ft_strdup(in->split_input[i]);
			j++;
			i++;
		}
		in->split_input[j] = NULL;
	}
	return(in->split_input);
}

void	check_redirs(t_input *in)
{
	int i;
	
	i = 0;
	in->is_infile = 0;
	while(in->split_input[i])
	{
		if (!(ft_strncmp(in->split_input[i], "<<", 3)))
		{
			if (in->split_input[i + 1] != NULL)
				here_doc(in, i);
			else
				error_msg(in, ERR_SYNTAX, -1);
		}
		i++;
	}
	i = 0;
	while (in->split_input[i])
	{
		if (!(ft_strncmp(in->split_input[i], "<", 2)))
		{
			if (in->split_input[i + 1] == NULL)
				error_msg(in, ERR_SYNTAX, -1);
			in->fd_in = open(in->split_input[i + 1], O_RDONLY);
			if (in->fd_in == -1)
				error_msg(in, ERR_FILE, i + 1);
			else
			{
				remove_redir(in, i);
				if (!(ft_strncmp(in->split_input[0], "", 2)))
					exit(0);
				if (!is_builtin(in))
					dup2(in->fd_in, STDIN_FILENO);
				close(in->fd_in);
				in->is_infile = 1;
			}
		}
		i++;
	}
}
