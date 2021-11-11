/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:55:39 by ldurante          #+#    #+#             */
/*   Updated: 2021/11/10 17:43:34 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pair_chars(char *arg, int c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (arg[i])
	{
		if (arg[i] == c)
			count++;
		i++;
	}
	return (count);
}

char	*delete_char(char *str, int c, int c_num)
{
	char	*str_final;
	int		i;
	int		pos;

	i = 0;
	pos = 0;
	str_final = malloc(sizeof(char) * (ft_strlen(str) - c_num + 1));
	while (str[i])
	{
		if (str[i] != c)
		{
			str_final[pos] = str[i];
			pos++;
		}
		i++;
	}
	str_final[pos] = '\0';
	return (str_final);
}

char	**check_quotes(char **user_input)
{
	int		i;
	int		count;
	char	*string;
	
	i = 0;
	while (user_input[i] != NULL)
	{
		count = pair_chars(user_input[i], '"');
		if (count % 2 == 0)
		{
			string = delete_char(user_input[i], '"', count);
			free(user_input[i]);
			user_input[i] = string;
		}
		count = pair_chars(user_input[i], '\'');
		if (count % 2 == 0)
		{
			string = delete_char(user_input[i], '\'', count);
			free(user_input[i]);
			user_input[i] = string;
		}
		i++;
		// len = ft_strlen(user_input[i]);
		// last = len - 1;
		// if (user_input[i][0] == '"' && user_input[i][last] == '"')
		// 	user_input[i] = ft_substr(user_input[i], 1, len - 2);
		// if (user_input[i][0] == '\'' && user_input[i][last] == '\'')
		// 	user_input[i] = ft_substr(user_input[i], 1, len - 2);
	}
	return (user_input);
}

void	read_input(t_input *in)
{
	char	*prompt;

	prompt = ft_strjoin(getenv("USER"), "@minishell$ ");
	in->user_input = readline(prompt);
	add_history(in->user_input);
	in->split_input = ft_split(in->user_input, ' ');
	check_quotes(in->split_input);
	free(prompt);
	if (in->split_input[0] != NULL)
		builtins(in);
}
