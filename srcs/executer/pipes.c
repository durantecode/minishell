/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:04:12 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/31 19:38:22 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_builtin_hdoc(t_input *in, t_list *arg_list)
{
	t_arg	*aux;
	int		i;

	i = 0;
	aux = (t_arg *)arg_list->content;
	in->split_in = matrix_dup(aux->arg);
	in->q_state = aux->quotes;
	if (ft_lstsize(arg_list) == 1 && in->is_hdoc)
	{
		if (in->split_in && (is_builtin(in) || is_builtin2(in)))
		{
			while (in->split_in[i])
			{
				if (!(ft_strncmp(in->split_in[i], "<<", 3))
					&& in->q_state[i] == 0)
				{
					remove_redir(in, i);
					i--;
				}
				i++;
			}
			exec_args(in);
		}
	}
	free_matrix(in->split_in);
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
	if (in->is_outfile)
		close(in->back_stdout);
	if (in->split_in[0])
	{
		if (is_builtin(in) && !in->total_pipes)
			exit (g_exit_status);
		else
			exec_args(in);
	}
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
	while (aux_list && WIFEXITED(in->status))
	{
		if (pipe(in->fd[index % 2]) == -1)
			error_msg(in, ERR_PIPE, -1, 0);
		aux = (t_arg *)aux_list->content;
		in->split_in = aux->arg;
		in->q_state = aux->quotes;
		if_minishell(in);
		sub_pipex(in, aux_list, index, &flag);
		aux_list = aux_list->next;
		index++;
	}
	kill_last_process(in, flag);
	exec_builtin_hdoc(in, arg_list);
	free_list(in, arg_list);
}
