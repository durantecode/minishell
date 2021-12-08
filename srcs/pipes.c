/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:04:12 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/08 01:32:08 by ldurante         ###   ########.fr       */
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

void	pipex(t_input * in, t_list *arg_list)
{
	t_arg	*aux;
	t_list	*aux_list;
	pid_t	pid;
	int		indice = 0;
	int		fd[2][2];

	aux_list = arg_list;
	// aux = (t_arg *)aux_list->content;
	while (aux_list)
	{
		pipe(fd[indice % 2]);
		aux = (t_arg *)aux_list->content;
		// if (pipe(aux->pipe_fd) == -1)
		// 	printf("Error pipe\n");
		//write(1, ft_itoa(indice), 1);
		pid = fork();
		if (pid < 0)
		{
			/* cerrar FD's + errpr */
			printf("Error fork\n");
		}
		if (pid == 0)
		{
			if (aux_list->next != NULL)
				dup2(fd[indice % 2][W_END], STDOUT_FILENO);
			close(fd[indice % 2][W_END]);
			if (indice > 0)
				dup2(fd[(indice + 1) % 2][R_END], STDIN_FILENO);
			close(fd[(indice + 1) % 2][R_END]);
			// printf("hola\n");
			// free_matrix(in->split_input);
			in->split_input = aux->arg;
			builtins(in);
			exit(0);
		}
		waitpid(pid, NULL, 0);
		close(fd[indice % 2][W_END]);
		//write(1, "F\n", 2);
		// if (aux_list->next != NULL)
		// {
		// //	dup2(aux->pipe_fd[R_END], 1);
		// 	dup2(aux->pipe_fd[R_END], STDIN_FILENO);
		// 	close(aux->pipe_fd[R_END]);
		// }
		aux_list = aux_list->next;
		indice++;
		in->split_input = aux->arg;
	}
}

void	init_arg_list(t_input *in)
{
	t_arg	*args;
	t_arg	*aux;
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
		args->arg = malloc(sizeof(char *) * i[2] + 1);
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
	
	// while (arg_list)
	// {
	// 	aux = (t_arg *)arg_list->content;
	// 	print_matrix(aux->arg);
	// 	printf("-------\n");
	// 	arg_list = arg_list->next;
	// }
	(void)aux;
}