/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:03:38 by ldurante          #+#    #+#             */
/*   Updated: 2021/11/10 18:26:29 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	leaks(void)
{
	system("leaks minishell");
}

void	init_structs(t_input *in, t_list **envp)
{
	in->user_input = NULL;
	in->split_path = ft_split(getenv("PATH"), ':');
	in->split_input = NULL;
	in->cmd_path = NULL;
	in->env_list = envp;
}

char	*ft_getenv(const char *str, t_input *in)
{
	t_list	*aux;
	int		size_var;
	int		total_size;

	aux = *in->env_list;
	while (aux)
	{
		size_var = ft_strlen(str);
		total_size = ft_strlen(aux->content);
		if (!(ft_strncmp(str, aux->content, size_var)))
			return (ft_substr(aux->content, size_var + 1, total_size - size_var));
		aux = aux->next;
	}
	return (NULL);
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

int	main(void)
{
	t_input	in;
	t_list	*envp;
	struct	sigaction	sa;
	
	// atexit(leaks);
	envp = NULL;
	init_env_list(&envp);
	init_structs(&in, &envp);
	sa.sa_sigaction = catch_signal;
	while (1)
	{
		sigaction(SIGINT, &sa, NULL);
		read_input(&in);
	}
	return (0);
}
