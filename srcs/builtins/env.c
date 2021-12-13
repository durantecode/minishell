/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 20:02:43 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/13 15:23:26 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env(t_input *in)
{
	t_list	*aux;

	aux = *in->env_list;
	while (aux)
	{
		printf("%s\n", (char *)aux->content);
		aux = aux->next;
	}
}

char	*ft_getenv(const char *str, t_input *in)
{
	t_list	*aux;
	char	*var;
	int		size_var;
	int		total_size;

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

void	dup_env(t_input *in, char **environ)
{
	int	i;

	i = 0;
	in->dup_env = NULL;
	if (!(*environ))
	{
		in->dup_env = malloc(sizeof(char *) * 5);
		in->dup_env[0] = ft_strjoin("PWD=", getcwd(NULL, 0));
		in->dup_env[1] = ft_strdup("SHLVL=0");
		in->dup_env[2] = ft_strdup("_=/usr/bin/env");
		in->dup_env[3]
			= ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
		in->dup_env[4] = NULL;
	}
	else
	{
		while (environ[i] != NULL)
			i++;
		in->dup_env = malloc(sizeof(char *) * i);
		i = -1;
		while (environ[++i])
			in->dup_env[i] = ft_strdup(environ[i]);
		in->dup_env[i] = NULL;
	}
}

void	init_env_list(t_input *in, t_list **envp, char **environ)
{
	int		i;
	int		size;

	i = 0;
	in->old_environ = environ;
	dup_env(in, environ);
	while (in->dup_env[i] != NULL)
	{
		size = ft_strlen(in->dup_env[i]);
		ft_lstadd_back(envp, ft_new_node((void *) in->dup_env[i], size + 1));
		i++;
	}
}
