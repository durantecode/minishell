/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:04:12 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/25 14:22:28 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* REVISAR LONGITUD FUNCIONES */

int	count_pipes(t_input *in)
{
	int	i;
	int	pipes;

	i = 0;
	pipes = 1;
	while (in->split_input[i] != NULL)
	{
		if (!(ft_strncmp(in->split_input[i], "|", 2)))
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

	index = 0;
	aux_list = arg_list;
	while (aux_list)
	{
		if (pipe(fd[index % 2]) == -1)
			printf("Error pipe\n");
		aux = (t_arg *)aux_list->content;
		signal(SIGINT, handler2);
		signal(SIGQUIT, handler2);
		pid = fork();
		if (pid < 0)
		{
			close(fd[index % 2][W_END]);
			close(fd[index % 2][R_END]);
			printf("Error fork\n");
		}
		else if (pid == 0)
		{
			if (aux_list->next != NULL)
				dup2(fd[index % 2][W_END], STDOUT_FILENO);
			close(fd[index % 2][W_END]);
			if (index > 0)
			{
				if (in->fd_in < 3)
					dup2(fd[(index + 1) % 2][R_END], STDIN_FILENO);
			}
			close(fd[(index + 1) % 2][R_END]);
			in->split_input = aux->arg;
			exec_args(in);
			free_matrix(in->split_input);
			free(in->cmd_path);
			exit (0);
		}
		waitpid(pid, NULL, 0);
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
		while (in->split_input[i[0]] != NULL && (ft_strncmp(in->split_input[i[0]], "|", 2)))
		{
			i[0]++;
			i[2]++;
		}
		args = malloc(sizeof(t_arg));
		args->arg = malloc(sizeof(char *) * (i[2] + 1));
		i[0] = i[0] - i[2];
		while (in->split_input[i[0]] != NULL && (ft_strncmp(in->split_input[i[0]], "|", 2)))
		{
			args->arg[i[3]] = ft_strdup(in->split_input[i[0]]);
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
