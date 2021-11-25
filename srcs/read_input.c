/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:55:39 by ldurante          #+#    #+#             */
/*   Updated: 2021/11/24 23:56:15 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pair_chars(char *arg)
{
	int	i;
	int	count_single;
	int	count_double;
	int	flag_simple;
	int	flag_double;

	i = 0;
	count_single = 0;
	count_double = 0;
	flag_double = 0;
	flag_simple = 0;
	while (arg[i])
	{
		if (arg[i] == '"' && flag_simple == 0 && flag_double == 0)
		{
			count_double++;
			flag_double = 1;
		}
		else if (arg[i] == '"' && flag_simple == 0 && flag_double == 1)
		{
			count_double++;
			flag_double = 0;
		}
		else if (arg[i] == '\'' && flag_simple == 0 && flag_double == 0)
		{
			count_single++;
			flag_simple = 1;
		}
		else if (arg[i] == '\'' && flag_simple == 1 && flag_double == 0)
		{
			count_single++;
			flag_simple = 0;
		}
		i++;
	}
	return (count_double % 2 == 0 + count_single % 2 == 0);
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

char	*separate_pipes(char *input)
{
	int		i;
	char	*final_input;
	int		flag;
	int		count;

	count = 0;
	flag = 0;
	i = 0;
	while (input[i])
	{
		if ((input[i] == '"' || input[i] == '\'') && flag == 0)
			flag = 1;
		else if ((input[i] == '"' || input[i] == '\'') && flag == 1)
			flag = 0;
		if (flag == 0 && input[i] == '|')
			count += 2;
		count++;
		i++;
	}
	final_input = malloc(sizeof(char) * count);
	count = 0;
	i = 0;
	while (input[i])
	{
		if ((input[i] == '"' || input[i] == '\'') && flag == 0)
			flag = 1;
		else if ((input[i] == '"' || input[i] == '\'') && flag == 1)
			flag = 0;
		if (flag == 0 && input[i] == '|')
		{
			final_input[count++] = ' ';
			final_input[count++] = input[i];
			final_input[count] = ' ';
		}
		else
			final_input[count] = input[i];
		count++;
		i++;
	}
	final_input[count] = '\0';
	return (final_input);
}

void	read_input(t_input *in)
{
	char	*prompt;
	char	*user;
	char	*aux;

	user = ft_getenv("USER", in);
	if (!user)
		user = ft_strdup("guest");
	prompt = ft_strjoin(user, "@minishell> $ ");
	in->user_input = readline(prompt);
	if (pair_chars(in->user_input) == 0)
	{
		aux = in->user_input;
		in->user_input = separate_pipes(in->user_input);
		free(aux);
		in->split_input = check_args(in);
		expand_vars(in);
		in->split_input = quotes(in->split_input);
		if (in->split_input[0] != NULL)
			builtins(in);
		free(user);
	}
	else
		printf("minishell: Invalid argument\n");
	if (in->user_input[0] != '\0')
		add_history(in->user_input);
	free(prompt);
}
