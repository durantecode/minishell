/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:33:39 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/13 11:51:29 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cd(t_input *in)
{
	char	*home_path;
	char	*aux;
	char	*full_path;
	char	*pwd;

	home_path = ft_getenv("HOME", in);
	pwd = getcwd(NULL, 0);
	if (!in->split_input[1] || !(ft_strncmp(in->split_input[1], "", 2)))
	{
		if (chdir(home_path) == -1)
			error_msg(in, ERR_HOME, 0, 0);
	}
	else if (in->split_input[1][0] == '~')
	{
		if (in->split_input[1][1] == '\0')
			chdir(home_path);
		else
		{
			aux = in->split_input[1];
			aux++;
			full_path = ft_strjoin(home_path, aux);
			free(in->split_input[1]);
			in->split_input[1] = ft_strdup(full_path);
			cd(in);
			free(full_path);
		}
	}
	else if (chdir(in->split_input[1]) != 0)
		error_msg(in, ERR_FILE, 1, 0);
	free(home_path);
	update_env_var(in, "OLDPWD=", pwd);
	free(pwd);
	pwd = getcwd(NULL, 0);
	update_env_var(in, "PWD=", pwd);
	free(pwd);
}
