/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 20:02:43 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/06 19:03:30 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env(t_input *in, int type)
{
	t_list	*aux;

	if (in->split_input[1] != NULL)
	{
		error_msg(in, ERR_FILE, 1);
		return ;
	}
	aux = *in->env_list;
	if (!type)
	{
		while (aux)
		{
			if (ft_strchr(aux->content, '='))
				printf("%s\n", (char *)aux->content);
			aux = aux->next;
		}
	}
	else
	{
		while (aux)
		{
			printf("declare -x %s\n", (char *)aux->content);
			aux = aux->next;
		}
	}
}

char	*ft_getenv(const char *str, t_input *in)
{
	t_list	*aux;
	char	*var;
	int		size_var;
	int		total_size;

	aux = *in->env_list;
	var = NULL;
	while (aux)
	{
		size_var = ft_strlen(str);
		if (!(ft_strncmp(str, aux->content, size_var)) && ((char *)aux->content)[size_var] == '\0')
		{
			var = ft_strdup(aux->content);
			free(aux->content);
			aux->content = ft_strjoin(var, "=");
			free(var);
			return(ft_getenv(str, in));
		}
		aux = aux->next;
	}
	aux = *in->env_list;
	var = ft_strjoin(str, "=");
	while (aux)
	{
		size_var = ft_strlen(var);
		total_size = ft_strlen(aux->content);
		if (!(ft_strncmp(var, aux->content, size_var)))
		{
			free(var);
			return (ft_substr(aux->content, size_var, total_size - size_var));
		}
		aux = aux->next;
	}
	free(var);
	return (NULL);
}

void	check_basic_vars(t_input *in)
{
	char	*aux;
	char	*pwd;
	
	aux = ft_getenv("PATH", in);
	if (!aux)
		update_env_var(in, "PATH=", "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	else
		free(aux);
	aux = ft_getenv("SHLVL", in);
	if (!aux)
		update_env_var(in, "SHLVL=", "0");
	else
		free(aux);
	aux = ft_getenv("PWD", in);
	if (!aux)
	{
		pwd = getcwd(NULL, 0);
		update_env_var(in, "PWD=", pwd);
		free(pwd);
	}
	else
		free(aux);
	aux = ft_getenv("_", in);
	if (!aux)
		update_env_var(in, "_=", "env");
	else
		free(aux);
}

void	dup_env(t_input *in, char **environ)
{
	int		i;
	char	*pwd;

	i = 0;
	in->dup_env = NULL;
	pwd = getcwd(NULL, 0);
	if (!(*environ))
	{
		in->dup_env = malloc(sizeof(char *) * 5);
		in->dup_env[0]
			= ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
		in->dup_env[1] = ft_strjoin("PWD=", pwd);
		in->dup_env[2] = ft_strdup("SHLVL=0");
		in->dup_env[3] = ft_strdup("_=env");
		in->dup_env[4] = NULL;
	}
	else
	{
		while (environ[i] != NULL)
			i++;
		in->dup_env = malloc(sizeof(char *) * (i + 1));
		i = 0;
		while (environ[i])
		{
			in->dup_env[i] = ft_strdup(environ[i]);
			i++;
		}
		in->dup_env[i] = NULL;
	}
	free(pwd);
}

void	init_env_list(t_input *in, t_list **envp, char **environ)
{
	int		i;
	int		size;

	size = 0;
	i = 0;
	in->old_environ = environ;
	dup_env(in, environ);
	while (in->dup_env[i] != NULL)
	{
		size = ft_strlen(in->dup_env[i]);
		ft_lstadd_back(envp, ft_new_node((void *) in->dup_env[i], size + 1));
		i++;
	}
	// check_basic_vars(in);
}
