/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:50:08 by ldurante          #+#    #+#             */
/*   Updated: 2021/11/24 20:42:04 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pair_quotes(char *arg, int c)
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

char	*delete_quote(char *str, int c, int c_num)
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

char	**quotes(char **user_input, t_input *in)
{
	int		i;
	int		count;
	char	*string;
	
	i = 0;
	while (user_input[i] != NULL)
	{
		if ((count = pair_quotes(user_input[i], '"')) % 2 == 0)
		// if (count % 2 == 0)
		{
			string = delete_quote(user_input[i], '"', count);
			free(user_input[i]);
			user_input[i] = string;
		}
		else if ((count = pair_quotes(user_input[i], '\'')) % 2 == 0)
		// else if (count % 2 == 0)
		{
			string = delete_quote(user_input[i], '\'', count);
			free(user_input[i]);
			user_input[i] = string;
		}
		i++;
	}
	(void)in;
	return (user_input);
}
