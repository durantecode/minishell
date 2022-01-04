/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:33:39 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/04 18:37:38 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	update_oldpwd(t_input *in, char *old_pwd)
// {
// 	char	*update_old_pwd;

// 	update_old_pwd = ft_strjoin("OLDPWD=", old_pwd);
// 	free(old_pwd);
// 	free_matrix(in->split_input);
// 	in->split_input = malloc(sizeof(char *) * 3);
// 	in->split_input[0] = ft_strdup("export");
// 	in->split_input[1] = update_old_pwd;
// 	in->split_input[2] = NULL;
// 	export(in);
// }

// void	update_pwd(t_input *in)
// {
// 	char	*new_pwd;
// 	char	*aux;
	
// 	aux = getcwd(NULL, 0);
// 	new_pwd = ft_strjoin("PWD=", aux);
// 	free(aux);
// 	free_matrix(in->split_input);
// 	in->split_input = malloc(sizeof(char *) * 3);
// 	in->split_input[0] = ft_strdup("export");
// 	in->split_input[1] = new_pwd;
// 	in->split_input[2] = NULL;
// 	export(in);
// }

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
	update_env_var(in, "OLDPWD=", old_pwd);
	update_env_var(in, "PWD=", getcwd(NULL, 0));
}
