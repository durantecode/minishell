/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:55:39 by ldurante          #+#    #+#             */
/*   Updated: 2021/11/11 12:06:19 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**check_quotes(char **user_input)
{
	int i;
	int	last;
	int len;

	i = 0;
	while (user_input[i] != NULL)
	{
		len = ft_strlen(user_input[i]);
		last = len - 1;
		if (user_input[i][0] == '"' && user_input[i][last] == '"')
			user_input[i] = ft_substr(user_input[i], 1, len - 2);
		if (user_input[i][0] == '\'' && user_input[i][last] == '\'')
			user_input[i] = ft_substr(user_input[i], 1, len - 2);
		i++;
	}
	return (user_input);
}

void	read_input(t_input *in)
{
	char	*prompt;
	char	*user;

	user = ft_getenv("USER", in);
	if (!user)
		user = ft_strdup("guest");
	prompt = ft_strjoin(user, "@minishell$ ");
	in->user_input = readline(prompt);
	add_history(in->user_input);
	in->split_input = ft_split(in->user_input, ' ');
	check_quotes(in->split_input);
	free(prompt);
	if (in->split_input[0] != NULL)
		builtins(in);
}
