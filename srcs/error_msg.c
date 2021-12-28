/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:58:27 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/28 13:07:50 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	update_exit_status(char *ERR)
{
	if (!ft_strncmp(ERR, "ERR_CMD", 8))
		return (127);
	if (!ft_strncmp(ERR, "ERR_FILE", 9))
		return (1);
	if (!ft_strncmp(ERR, "ERR_SYNTAX", 11))
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
	in->is_err = 1;
	return (0);
}
