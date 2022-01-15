/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:58:27 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/15 19:49:02 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	update_exit_status(char *ERR, int is_abs)
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
	return(1);
}

int	error_msg(t_input *in, char *MSG, int n, int is_abs)
{
	if (in->total_pipes > 0 && in->is_hdoc)
		in->fd_error = open(".err_tmp", O_CREAT | O_WRONLY | O_APPEND, 0666);
	else
		in->fd_error = 2;
	if (n >= 0)
	{
		ft_putstr_fd(SHELL, in->fd_error);
		ft_putstr_fd(in->split_input[n], in->fd_error);
		ft_putstr_fd(": ", in->fd_error);
		ft_putendl_fd(MSG, in->fd_error);
	}
	else
	{
		ft_putstr_fd(SHELL, in->fd_error);
		ft_putendl_fd(MSG, in->fd_error);
	}
	close(in->fd_error);
	if (in->split_input && !is_builtin(in) && n != -2)
		exit(update_exit_status(MSG, is_abs));
	exit_status = update_exit_status(MSG, is_abs);
	in->is_err = 1;
	return (0);
}
