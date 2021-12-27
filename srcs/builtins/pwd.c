/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:37:56 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/26 21:54:44 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	// ft_putendl_fd(pwd, 1);
	printf("%s\n", pwd);
	free(pwd);
}
