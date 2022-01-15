/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:05:11 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/15 19:18:19 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_redir(t_input *in, int i)
{
	int j;
	char **aux;

	j = 0;
	aux = malloc(sizeof(char *) * (matrix_len(in->split_input) - 1));
	while(in->split_input[j] && j < i)
	{
		aux[j] = ft_strdup(in->split_input[j]);
		j++;
	}
	i += 2; 
	while(in->split_input[i])
	{
		aux[j] = ft_strdup(in->split_input[i]);
		in->quote_state[j] = in->quote_state[i];
		j++;
		i++;
	}
	aux[j] = NULL;
	free_matrix(in->split_input);
	in->split_input = NULL;
	in->split_input = aux;
}

void	here_doc(t_input *in, int i)
{
	char	*eof;
	int		fd;
	char	*here_doc;

	fd = open(".hd_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd == -1)
		error_msg(in, ERR_FILE, -1, 0);
	eof = ft_strdup(in->split_input[i + 1]);
	free(in->prompt);
	in->prompt = ft_strdup("> ");
	while (1)
	{
		here_doc = readline(in->prompt);
		if (!here_doc || !(ft_strncmp(here_doc, eof, ft_strlen(eof))))
			break ;
		write(fd, here_doc, ft_strlen(here_doc));
		write(fd, "\n", 1);
		free(here_doc);
	}
	close(fd);
	free(here_doc);
	remove_redir(in, i);
	exec_hdoc(in);
	if (!in->split_input[0])
		return ;
	fd = open(".hd_tmp", O_RDONLY);
	if (!is_builtin(in))
		dup2(fd, STDIN_FILENO);
	close(fd);
	in->is_hdoc = 1;
}
