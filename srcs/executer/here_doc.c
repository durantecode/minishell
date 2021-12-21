/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:05:11 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/22 00:40:44 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**remove_heredoc(t_input *in, int i, char **full_doc)
{
	int j;

	j = i;
	i += 3;
	if (in->split_input[i] == NULL && in->split_input[0][0] == '<')
		in->split_input[0] = ft_strdup("");
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
	free_matrix(full_doc);
	return(in->split_input);
}

void	here_doc(t_input *in, int i)
{
	char	*here_doc;
	char	*delimiter;
	char	**full_doc;
	char	*line;
	// int		tmp_fd;

	line = ft_strdup("");
	full_doc = malloc(sizeof(char *));
	full_doc[0] = NULL;
	// print_matrix(in->split_input);
	delimiter = in->split_input[i + 2];
	in->prompt = ft_strdup("> ");
	while (1)
	{
		here_doc = readline(in->prompt);
		if (!(ft_strncmp(here_doc, delimiter, ft_strlen(delimiter))))
			break ;
		line = ft_strjoin3(line, here_doc, "\n");
		// write(tmp_fd, here_doc, ft_strlen(here_doc));
		// write(tmp_fd, "\n", 1);
		full_doc = matrix_add_back(full_doc, here_doc);
	}
	write(0, line, ft_strlen(line));
	// free(here_doc);
	// remove_heredoc(in, i, full_doc);
	// exec_args(in);
}


