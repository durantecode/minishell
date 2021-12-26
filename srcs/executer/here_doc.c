/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:05:11 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/26 22:36:34 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**remove_redir(t_input *in, int i, char c)
{
	int j;

	j = i;
	i += 2;
	if (in->split_input[i] == NULL && in->split_input[0][0] == c)
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

void	here_doc(t_input *in, int i)
{
	char	*delimiter;
	int		fd;
	char	*here_doc;

	fd = open(".hd_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd == -1)
		error_msg(in, ERR_FILE, -1);
	delimiter = in->split_input[i + 1];
	in->prompt = ft_strdup("> ");
	while (1)
	{
		here_doc = readline(in->prompt);
		if (!(ft_strncmp(here_doc, delimiter, ft_strlen(delimiter))))
			break ;
		write(fd, here_doc, ft_strlen(here_doc));
		write(fd, "\n", 1);
		free(here_doc);
	}
	close(fd);
	remove_redir(in, i, '<');
	if (!(ft_strncmp(in->split_input[0], "", 2)))
		exit(0);
	in->fd_hdoc = open(".hd_tmp", O_RDONLY);
	if (!is_builtin(in))
		dup2(in->fd_hdoc, STDIN_FILENO);
	close(in->fd_hdoc);
}


