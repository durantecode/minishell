/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 03:03:21 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/22 00:46:01 by ldurante         ###   ########.fr       */
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

char	**del_matrix_pos(char **matrix, int n)
{
	int		i;
	int		j;
	char	**aux;
	
	i = 0;
	j = 0;
	aux = malloc(matrix_len(matrix));
	while (matrix[i])
	{
		if (i == n)
			i++;
		aux[j] = matrix[i];
		i++;
		j++;
	}
	aux[j] = NULL;
	return(aux);
}

void	join_redirs(t_input *in)
{
	if (!(ft_strncmp(in->split_input[0], "", 2)))
	{
		in->split_input[0] = ft_strdup(in->split_input[1]);
		if (in->split_input[2] != NULL)
		{
			in->split_input[1] = ft_strdup(in->split_input[2]);
			if (in->split_input[3] != NULL)
				in->split_input = del_matrix_pos(in->split_input, 2);
			else
				in->split_input = del_matrix_pos(in->split_input, 1);
		}
		else
			in->split_input[1] = NULL;
	}
}

void	check_redirs(t_input *in)
{
	int i;
	pid_t pid;
	
	i = 0;
	join_redirs(in);
	while(in->split_input[i])
	{
		if (in->split_input[i][0] == '<')
		{
			// i++;
			if (in->split_input[i + 1] != NULL)
			{
				if (!(ft_strncmp(in->split_input[i + 1], "<", 2)))
				{
					// printf("|%s|\n", in->split_input[2]);
					if (in->split_input[i + 2] != NULL)
						// printf("call here_doc\n");
						here_doc(in, i);
					else
						error_msg(in, ERR_SYNTAX, -1);	
				}
			}
		}
		i++;
	}
	i = 0;
	while(in->split_input[i])
	{
		if (in->split_input[i][0] == '<')
		{
			in->fd_in = open(in->split_input[i + 1], O_RDONLY);
			if (in->fd_in == -1)
				error_msg(in, ERR_FILE, i);
			else
			{
				remove_redir(in, i);
				pid = fork();
				if (pid == 0)
				{
					// print_matrix(in->split_input);
					dup2(in->fd_in, STDIN_FILENO);
					if (!(ft_strncmp(in->split_input[0], "", 2)))
						exit(0);
					// free(in->user_input);
					close(in->fd_in);
					exec_args(in);
					exit(0);
					// printf("OEJTE\n");
				}
				waitpid(pid, NULL, 0);
				in->n_bytes = 1;
				// free(in->user_input);
				// in->user_input = NULL;
				// free_matrix(in->split_input);
				// in->split_input[0] = ft_strdup("");
				// printf("AA: |%s|\n", in->user_input);
				// print_matrix(in->split_input);
				// break ;

			}


					// error_msg(in, ERR_SYNTAX, -1);
		}
		i++;
	}
}
