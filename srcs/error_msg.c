/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:58:27 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/27 22:13:09 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	update_exit_status(char *ERR)
{
	if (ERR == ERR_CMD)
		return (127);
	if (ERR == ERR_FILE)
		return (1);
	if (ERR == ERR_SYNTAX)
		return (258);
	else
		return(1);
}

int	error_msg(t_input *in, char *MSG, int n)
{
	if (n >= 0)
	{
		write(2, SHELL, ft_strlen(SHELL));
		write(2, in->split_input[n], ft_strlen(in->split_input[n]));
		write(2, ": ", 2);
		write(2, MSG, ft_strlen(MSG));
		write(2, "\n", 1);
	}
	else
	{
		write(2, SHELL, ft_strlen(SHELL));
		write(2, MSG, ft_strlen(MSG));
		write(2, "\n", 1);
	}
	if (!is_builtin(in))
		exit(update_exit_status(MSG));
	exit_status = update_exit_status(MSG);
	return (0);
}
