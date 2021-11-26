/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 20:02:43 by ldurante          #+#    #+#             */
/*   Updated: 2021/11/25 23:52:46 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	init_env_list(t_list **envp)
{
	int		i;
	int		size;

	i = 0;
	while (environ[i] != NULL)
	{
		size = ft_strlen(environ[i]);
		ft_lstadd_back(envp, ft_new_node((void *) environ[i], size + 1));
		i++;
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