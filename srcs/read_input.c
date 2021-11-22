/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:55:39 by ldurante          #+#    #+#             */
/*   Updated: 2021/11/17 19:14:06 by dpavon-g         ###   ########.fr       */
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
	}
	return (user_input);
}

char	*separate_pipes(char *input)
{
	int i;
	char *final_input;
	int	flag;
	int	count;

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
	prompt = ft_strjoin(user, "@minishell$ ");
	in->user_input = readline(prompt);
	if (pair_chars(in->user_input, '"') % 2 == 0)
	{
		if (pair_chars(in->user_input, '\'') % 2 == 0)
		{
			if (in->user_input[0] != '\0')
				add_history(in->user_input);
			aux = in->user_input;
			in->user_input = separate_pipes(in->user_input);
			free(aux);
			in->split_input = check_args(in);
			if (in->split_input[0] != NULL)
				builtins(in);
			free(prompt);
		}
	}
	else
	{
		add_history(in->user_input);
		printf("minishell: Invalid argument\n");
		free(prompt);
	}
	
}