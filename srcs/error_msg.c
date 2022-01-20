/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:58:27 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/20 03:00:56 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_list(t_input *in, t_list *arg_list)
{
	t_arg	*aux;
	t_list	*aux_list;

	aux_list = arg_list;
	while (aux_list)
	{
		aux = (t_arg *)aux_list->content;
		free_matrix(aux->arg);
		free(aux->quotes);
		aux_list = aux_list->next;
	}
	ft_lstclear(&arg_list, free);
	in->q_state = NULL;
	in->split_in = NULL;
}

int	update_g_exit_status(char *ERR, int is_abs)
{
	if (!ft_strcmp(ERR, IS_DIR))
		return (126);
	else if (!ft_strcmp(ERR, ERR_PERM))
	{
		if (is_abs == 1)
			return (126);
	}
	else if (!ft_strcmp(ERR, ERR_FILE))
	{
		if (is_abs == 1)
			return (127);
	}
	else if (!ft_strcmp(ERR, ERR_CMD))
		return (127);
	else if (!ft_strcmp(ERR, ERR_SYNTAX))
		return (258);
	else if (!ft_strcmp(ERR, ERR_SYNTAX_PIPE))
		return (258);
	else if (!ft_strcmp(ERR, ERR_SYNTAX_IN))
		return (258);
	else if (!ft_strcmp(ERR, ERR_SYNTAX_OUT))
		return (258);
	return (1);
}

int	error_msg(t_input *in, char *MSG, int n, int is_abs)
{
	if (n >= 0)
	{
		ft_putstr_fd(SHELL, 2);
		ft_putstr_fd(in->split_in[n], 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(MSG, 2);
	}
	else
	{
		ft_putstr_fd(SHELL, 2);
		ft_putendl_fd(MSG, 2);
	}
	if (in->split_in && !is_builtin(in) && n != -2)
		exit(update_g_exit_status(MSG, is_abs));
	g_exit_status = update_g_exit_status(MSG, is_abs);
	in->is_err = 1;
	return (0);
}
