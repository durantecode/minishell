/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:04:12 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/02 00:32:51 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	return (pipes);
}

void	pipesito(t_input *in)
{
	int i;
	int j;
	pid_t	pid;
	int		pipe_fd[2];

	i = 0;
	j = 0;
			pipe(pipe_fd);
	while(in->split_input[i] != NULL)
		i++;
	in->split_arg = malloc(sizeof(char *) * i + 1);
	i = 0;
	while (in->split_input[i] != NULL)
	{
		if (!(ft_strncmp(in->split_input[i], "|", 2)))
		{
			pid = fork();
			if (pid == 0)
			{
				// if (p == 0)
				// {
					// print_matrix(in->split_arg);
					close(pipe_fd[R_END]);
					if (in->split_input[i + 1] != NULL)
						dup2(pipe_fd[W_END], STDOUT_FILENO);
					close(pipe_fd[W_END]);
					builtins(in);
				// }
				// else
				// {
				// 	ft_putendl_fd("OJETE\n", 1);
				// 	close(pipe_fd[W_END]);
				// 	dup2(pipe_fd[R_END], STDIN_FILENO);
				// 	close(pipe_fd[R_END]);
				// 	builtins(in);
				// }
				// exit(0);
			}
			// printf("%d\n", p);
			waitpid(pid, NULL, 0);
			if (in->split_input[i + 1] != NULL)
			{
				close(pipe_fd[W_END]);
				close(pipe_fd[R_END]);
				dup2(pipe_fd[R_END], STDIN_FILENO);
			}
			// free_matrix(in->split_arg);
			i++;
			j = 0;
		}
		if (in->split_input[i] != NULL)
		{
			// printf("AA: asda\n");
			in->split_arg[j] = ft_strdup(in->split_input[i]);
			i++;
			j++;
		}
	}
}

void	pipex(t_input * in, t_list *arg_list)
{
	t_arg *aux;
	t_list *aux_list;
	pid_t	pid;
	int		pipe_fd[2];
	// int i = 0;

	aux = NULL;
	aux_list = arg_list;
	// aux = (t_arg *)aux_list->next->content;
	// printf("%s\n", aux->arg[1]);
		if (pipe(pipe_fd) == -1)
			printf("Error pipe\n");
	while (aux_list)
	{
		aux = (t_arg *)aux_list->content;
		in->split_input = aux->arg;

		pid = fork();
		if (pid < 0)
		{
			/* cerrar FD's + errpr */
			printf("Error fork\n");
		}
		if (pid == 0)
		{
			close(pipe_fd[R_END]);
			if (aux_list->next != NULL)
				dup2(pipe_fd[W_END], STDOUT_FILENO);
			close(pipe_fd[W_END]);
			builtins(in);
			// exit(0);
		}
		waitpid(pid, NULL, 0);
		if (aux_list->next != NULL)
		{
			close(pipe_fd[W_END]);
			dup2(pipe_fd[R_END], STDIN_FILENO);
			close(pipe_fd[R_END]);
		}
		aux_list = aux_list->next;
		free_matrix(in->split_input);
	}
	
}

void	init_arg_list(t_input *in)
{
	// t_arg	*args;
	// t_list	*arg_list;
	// int		i[4];

	// i[0] = 0;
	// i[1] = 0;
	// arg_list = NULL;
	// while (i[1] < count_pipes(in))
	// {
	// 	i[3] = 0;
	// 	i[2] = 0;
	// 	while (in->split_input[i[0]] != NULL && (ft_strncmp(in->split_input[i[0]], "|", 2)))
	// 	{
	// 		i[0]++;
	// 		i[2]++;
	// 	}
	// 	args = malloc(sizeof(t_arg));
	// 	args->arg = malloc(sizeof(char *) * i[2] + 1);
	// 	i[0] = i[0] - i[2];
	// 	while (in->split_input[i[0]] != NULL && (ft_strncmp(in->split_input[i[0]], "|", 2)))
	// 	{
	// 		args->arg[i[3]] = ft_strdup(in->split_input[i[0]]);
	// 		i[0]++;
	// 		i[3]++;
	// 	}
	// 	args->arg[i[3]] = NULL;
	// 	ft_lstadd_back(&arg_list, ft_lstnew((void *) args));
	// 	i[1]++;
	// 	i[0]++;
	// }
	// t_arg *aux;
	// aux = NULL;
	// while (arg_list)
	// {
	// 	aux = (t_arg *)arg_list->content;
	// 	print_matrix(aux->arg);
	// 	arg_list = arg_list->next;
	// }
	// free_matrix(in->split_input);
	// pipex(in, arg_list);
	pipesito(in);
}