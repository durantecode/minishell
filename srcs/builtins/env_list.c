/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 10:25:41 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/20 10:27:10 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_getenv_aux(t_list *aux, char **var, int size_var)
{
	int	total_size;

	while (aux)
	{
		size_var = ft_strlen(*var);
		total_size = ft_strlen(aux->content);
		if (!(ft_strncmp(*var, aux->content, size_var)))
		{
			free(*var);
			return (ft_substr(aux->content, size_var, total_size - size_var));
		}
		aux = aux->next;
	}
	free(*var);
	return (NULL);
}

char	*ft_getenv(const char *str, t_input *in)
{
	t_list	*aux;
	char	*var;
	int		size_var;

	aux = *in->env_list;
	var = NULL;
	while (aux)
	{
		size_var = ft_strlen(str);
		if (!(ft_strncmp(str, aux->content, size_var))
			&& ((char *)aux->content)[size_var] == '\0')
		{
			var = ft_strdup(aux->content);
			free(aux->content);
			aux->content = ft_strjoin(var, "=");
			free(var);
			return (ft_getenv(str, in));
		}
		aux = aux->next;
	}
	aux = *in->env_list;
	var = ft_strjoin(str, "=");
	return (ft_getenv_aux(aux, &var, size_var));
}

void	init_basic_env(t_input *in, char **pwd)
{
	in->dup_env = malloc(sizeof(char *) * 5);
	in->dup_env[0]
		= ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	in->dup_env[1] = ft_strjoin("PWD=", (*pwd));
	in->dup_env[2] = ft_strdup("SHLVL=0");
	in->dup_env[3] = ft_strdup("_=./minishell");
	in->dup_env[4] = NULL;
}

void	dup_env(t_input *in, char **environ)
{
	int		i;
	char	*pwd;

	i = 0;
	in->dup_env = NULL;
	pwd = getcwd(NULL, 0);
	if (!(*environ))
		init_basic_env(in, &pwd);
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
	dup_env(in, environ);
	while (in->dup_env[i] != NULL)
	{
		size = ft_strlen(in->dup_env[i]);
		ft_lstadd_back(envp, ft_new_node((void *) in->dup_env[i], size + 1));
		i++;
	}
}
