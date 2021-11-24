/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:50:08 by ldurante          #+#    #+#             */
/*   Updated: 2021/11/24 18:54:18 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pair_quotes(char *arg, int c)
{
	int	i;
	int	count;

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

void	expand_flags(t_input *in)
{
	int	i;
	int	j;
	int	single_flag;

	i = -1;
	while (++i < 255)
		in->expand[i] = 0;
	i = 0;
	single_flag = 0;
	while (in->split_input[i] != NULL)
	{
		j = 0;
		while (in->split_input[i][j] != '\0')
		{
			if (in->split_input[i][j] == '\'')
				single_flag++;
			if (in->split_input[i][j] == '$' && single_flag % 2 != 0)
				in->expand[i] = 1;
			j++;
		}
		i++;
	}
}

char	*delete_quote(char *str)
{
	char	*str_final;
	int		i;
	int		len;
	int		flag_simple;
	int		flag_double;

	flag_double = 0;
	flag_simple = 0;
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '"' && flag_simple == 0 && flag_double == 0)
			flag_double = 1;
		else if (str[i] == '"' && flag_simple == 0 && flag_double == 1)
			flag_double = 0;
		else if (str[i] == '\'' && flag_simple == 0 && flag_double == 0)
			flag_simple = 1;
		else if (str[i] == '\'' && flag_simple == 1 && flag_double == 0)
			flag_simple = 0;
		else
			len++;
		i++;
	}
	str_final = malloc(sizeof(char) * (len + 1));
	i = 0;
	str_final[len] = '\0';
	len = 0;
	while (str[i])
	{
		if (str[i] == '"' && flag_simple == 0 && flag_double == 0)
			flag_double = 1;
		else if (str[i] == '"' && flag_simple == 0 && flag_double == 1)
			flag_double = 0;
		else if (str[i] == '\'' && flag_simple == 0 && flag_double == 0)
			flag_simple = 1;
		else if (str[i] == '\'' && flag_simple == 1 && flag_double == 0)
			flag_simple = 0;
		else
		{
			str_final[len] = str[i];
			len++;
		}
		i++;
	}
	return (str_final);
}

char	**quotes(char **user_input, t_input *in)
{
	int		i;
	char	*aux;

	i = 0;
	while (user_input[i] != NULL)
	{
		aux = user_input[i];
		user_input[i] = delete_quote(user_input[i]);
		free(aux);
		i++;
	}
	(void)aux;
	(void)in;
	return (user_input);
}
