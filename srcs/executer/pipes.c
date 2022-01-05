/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:04:12 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/05 12:54:51 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_pipes(t_input *in)
{
	int	i;
	int	pipes;

	i = 0;
	pipes = 1;
	while (in->split_input[i] != NULL)
	{
		if (!(ft_strncmp(in->split_input[i], "|", 2)) && in->quote_state[i] == 0)
			pipes++;
		i++;
	}
	in->total_pipes = pipes;
	return (pipes);
}

void handler2(int code)
{
	if (code == SIGINT)
	{
		write(2, "\n", 1);
	}
	else if (code == SIGQUIT)
	{
		write(2, "Quit: 3\n", 8);
	}
}

void	pipex(t_input *in, t_list *arg_list)
{
	t_arg	*aux;
	t_list	*aux_list;
	pid_t	pid;
	int		index;
	int		fd[2][2];
	int		status;
	int		size;

	size = 0;
	index = 0;
	aux_list = arg_list;
	while (aux_list)
	{
		if (pipe(fd[index % 2]) == -1)
			error_msg(in, ERR_PIPE, -1);
		aux = (t_arg *)aux_list->content;
		signal(SIGINT, handler2);
		signal(SIGQUIT, handler2);
		pid = fork();
		if (pid < 0)
		{
			close(fd[index % 2][W_END]);
			close(fd[index % 2][R_END]);
			error_msg(in, ERR_FORK, -1);
		}
		else if (pid == 0)
		{
			in->split_input = aux->arg;
			in->quote_state = aux->quotes;
			check_redirs(in);
			if (aux_list->next != NULL)
			{
				if (!in->is_outfile)
					dup2(fd[index % 2][W_END], STDOUT_FILENO);
			}
			close(fd[index % 2][W_END]);
			if (index > 0)
			{
				if (!in->is_infile && !in->is_hdoc)
					dup2(fd[(index + 1) % 2][R_END], STDIN_FILENO);
			}
			close(fd[(index + 1) % 2][R_END]);
			exec_args(in);
			free_matrix(in->split_input);
			free(in->cmd_path);
			exit (0);
		}
		waitpid(pid, &status, 0);
		exit_status = WEXITSTATUS(status);
		close(fd[index % 2][W_END]);
		aux_list = aux_list->next;
		index++;
		in->split_input = aux->arg;
	}
}

void	init_arg_list(t_input *in)
{
	t_arg	*args;
	t_list	*arg_list;
	int		i[4];

	i[0] = 0;
	i[1] = 0;
	arg_list = NULL;
	while (i[1] < count_pipes(in))
	{
		i[3] = 0;
		i[2] = 0;
		while (in->split_input[i[0]] != NULL && ((ft_strncmp(in->split_input[i[0]], "|", 2))
			|| in->quote_state[i[0]] == 1))
		{
			i[0]++;
			i[2]++;
		}
		args = malloc(sizeof(t_arg));
		args->arg = malloc(sizeof(char *) * (i[2] + 1));
		args->quotes = malloc(sizeof(int) * (i[2]));
		i[0] = i[0] - i[2];
		while (in->split_input[i[0]] != NULL && ((ft_strncmp(in->split_input[i[0]], "|", 2))
			|| in->quote_state[i[0]] == 1))
		{
			args->arg[i[3]] = ft_strdup(in->split_input[i[0]]);
			if (in->quote_state[i[0]] == 1)
				args->quotes[i[3]] = 1;
			else
				args->quotes[i[3]] = 0;
			i[0]++;
			i[3]++;
		}
		args->arg[i[3]] = NULL;
		ft_lstadd_back(&arg_list, ft_lstnew((void *) args));
		i[1]++;
		i[0]++;
	}
	free_matrix(in->split_input);
	pipex(in, arg_list);
}
