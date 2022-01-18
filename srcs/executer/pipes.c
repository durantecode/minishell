/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:04:12 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/18 21:55:57 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_pipes(t_input *in)
{
	int	i;
	int	pipes;

	i = 0;
	pipes = 0;
	while (in->split_in[i] != NULL)
	{
		if (!(ft_strncmp(in->split_in[i], "|", 2)) && in->q_state[i] == 0)
			pipes++;
		i++;
	}
	in->total_pipes = pipes;
	return (pipes);
}

void	child(t_input *in, t_list *aux_list, int index)
{
	check_redirs(in);
	if (aux_list->next != NULL)
	{
		if (!in->is_outfile)
			dup2(in->fd[index % 2][W_END], STDOUT_FILENO);
	}
	close(in->fd[index % 2][W_END]);
	if (index > 0)
	{
		close(in->fd[index % 2][W_END]);
		if (!in->is_infile)
			dup2(in->fd[(index + 1) % 2][R_END], STDIN_FILENO);
		close(in->fd[(index + 1) % 2][R_END]);
	}
	close(in->fd[index % 2][R_END]);
	if (in->split_in[0])
		exec_args(in);
	exit (g_exit_status);
}

void	sub_pipex(t_input *in, t_list *aux_list, int index, int *flag)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close(in->fd[index % 2][W_END]);
		close(in->fd[index % 2][R_END]);
		*flag = 1;
	}
	if (!pid)
		child(in, aux_list, index);
	close(in->fd[index % 2][W_END]);
	if (index == 0 && aux_list->next == NULL)
		close(in->fd[index % 2][R_END]);
	if (index > 0 && aux_list->next != NULL)
		close(in->fd[(index + 1) % 2][R_END]);
	if (index > 0 && aux_list->next == NULL)
	{
		close(in->fd[index % 2][R_END]);
		close(in->fd[(index + 1) % 2][R_END]);
	}
}

void	kill_last_process(t_input *in, int flag)
{
	if (flag)
		error_msg(in, ERR_FORK, -2, 0);
	while (in->total_pipes >= 0)
	{
		waitpid(-1, &in->status, 0);
		if (WIFEXITED(in->status))
			g_exit_status = WEXITSTATUS(in->status);
		in->total_pipes--;
	}
	if (g_exit_status == 250)
		g_exit_status = 1;
}

void	pipex(t_input *in, t_list *arg_list)
{
	t_arg	*aux;
	t_list	*aux_list;
	int		index;
	int		flag;

	index = 0;
	flag = 0;
	aux_list = arg_list;
	while (aux_list && g_exit_status != 130 && g_exit_status != 250)
	{
		if (pipe(in->fd[index % 2]) == -1)
			error_msg(in, ERR_PIPE, -1, 0);
		aux = (t_arg *)aux_list->content;
		in->split_in = aux->arg;
		in->q_state = aux->quotes;
		signal(SIGINT, handler2);
		signal(SIGQUIT, handler2);
		sub_pipex(in, aux_list, index, &flag);
		aux_list = aux_list->next;
		index++;
	}
	kill_last_process(in, flag);
	free_list(in, arg_list);
}

void	init_arg_list_aux(t_input *in, t_list **arg_list, int i[4])
{
	t_arg	*args;

	args = malloc(sizeof(t_arg));
	args->arg = malloc(sizeof(char *) * (i[2] + 1));
	args->quotes = malloc(sizeof(int) * (i[2]));
	i[0] = i[0] - i[2];
	while (in->split_in[i[0]] != NULL
		&& ((ft_strncmp(in->split_in[i[0]], "|", 2))
			|| in->q_state[i[0]] == 1))
	{
		args->arg[i[3]] = ft_strdup(in->split_in[i[0]]);
		if (in->q_state[i[0]] == 1)
			args->quotes[i[3]] = 1;
		else
			args->quotes[i[3]] = 0;
		i[0]++;
		i[3]++;
	}
	args->arg[i[3]] = NULL;
	ft_lstadd_back(arg_list, ft_lstnew((void *) args));
}

void	init_arg_list(t_input *in)
{
	t_list	*arg_list;
	int		i[4];

	i[0] = 0;
	i[1] = 0;
	arg_list = NULL;
	while (i[1] <= in->total_pipes)
	{
		i[3] = 0;
		i[2] = 0;
		while (in->split_in[i[0]] != NULL
			&& ((ft_strncmp(in->split_in[i[0]], "|", 2))
				|| in->q_state[i[0]] == 1))
		{
			i[0]++;
			i[2]++;
		}
		init_arg_list_aux(in, &arg_list, i);
		i[1]++;
		i[0]++;
	}
	free(in->q_state);
	free_matrix(in->split_in);
	pipex(in, arg_list);
}
