/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:58:27 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/26 15:24:22 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	TIPOS DE ERRORES:

	Comando no encontrado					--> 127
	Archivo no encontrado o bad argument	--> 2
	Comando ejecutado satisfactoriamente	--> 0
	Argumentos invalidos					--> 1
	Hacer ctrl+c							--> 130
	Hacer ctrl+\							--> 131
	Hacer ctrl+d							--> No debe de hacer nada

*/

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
		exit(0);
	// exit_status = 127;
	return (0);
}
