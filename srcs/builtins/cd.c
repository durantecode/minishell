/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:33:39 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/28 20:08:42 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_oldpwd(t_input *in, char *old_pwd)
{
	char	*update_old_pwd;

	update_old_pwd = ft_strjoin("OLDPWD=", old_pwd);
	free(old_pwd);
	free_matrix(in->split_input);
	in->split_input = malloc(sizeof(char *) * 3);
	in->split_input[0] = ft_strdup("export");
	in->split_input[1] = ft_strdup(update_old_pwd);
	in->split_input[2] = NULL;
	free(update_old_pwd);
	export(in);
}

void	update_pwd(t_input *in)
{
	char	*new_pwd;
	char	*aux;
	
	aux = getcwd(NULL, 0);
	new_pwd = ft_strjoin("PWD=", aux);
	free(aux);
	free_matrix(in->split_input);
	in->split_input = malloc(sizeof(char *) * 3);
	in->split_input[0] = ft_strdup("export");
	in->split_input[1] = ft_strdup(new_pwd);
	in->split_input[2] = NULL;
	free(new_pwd);
	export(in);
}

void	cd(t_input *in)
{
	char	*home_path;
	char	*aux;
	char	*full_path;
	char	*old_pwd;

	home_path = ft_getenv("HOME", in);
	old_pwd = getcwd(NULL, 0);
	if (!in->split_input[1] || !(ft_strncmp(in->split_input[1], "", 2)))
	{
		if (chdir(home_path) == -1)
			error_msg(in, ERR_HOME, 0);
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
		error_msg(in, ERR_FILE, 1);
	free(home_path);
	update_oldpwd(in, old_pwd);
	update_pwd(in);
}
