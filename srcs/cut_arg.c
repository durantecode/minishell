/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 19:23:22 by ldurante          #+#    #+#             */
/*   Updated: 2021/11/15 20:02:43 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static int	ft_count_string(const char *s)
// {
// 	int		count;
// 	int		i;
// 	char	c;
// 	int		flag;

// 	flag = 0;
// 	count = 0;
// 	c = ' ';
// 	i = 0;
// 	while(s[i])
// 	{
// 		if (s[i] == '"' && flag == 0)
// 		{
// 			flag = 1;
// 			c = '"';
// 		}
// 		else if (s[i] == '"' && flag == 1)
// 		{
// 			flag = 0;
// 			c = ' ';
// 			i++;
// 		}
// 		if (s[i] != c && s[i])
// 		{
// 			count++;
// 			while (s[i] != c && s[i] != '\0')
// 				i++;
// 		}
// 		else if (s[i] != '\0')
// 			i++;
// 	}
// 	return (count);
// }

// static int	ft_count_chars(const char *s, char c, int i)
// {
// 	int		counter;

// 	counter = 0;
// 	if (!s)
// 		return (0);
// 	while (s[i] != '\0' && s[i] != c)
// 	{
// 		counter++;
// 		i++;
// 	}
// 	return (counter);
// }

// static char	**ft_write_string(char const *s, char **dst, int numstr)
// {
// 	int		i;
// 	int		j;
// 	int		k;
// 	char	c;
// 	int		flag;

// 	c = ' ';
// 	i = 0;
// 	j = 0;
// 	flag = 0;
// 	while (s[i] && j < numstr)
// 	{
// 		if (s[i] == '"' && flag == 0)
// 		{
// 			flag = 1;
// 			c = '"';
// 		}
// 		else if (s[i] == '"' && flag == 1)
// 		{
// 			flag = 0;
// 			c = ' ';
// 			i++;
// 		}
// 		k = 0;
// 		while (s[i] == c && s[i])
// 			i++;
// 		dst[j] = malloc(sizeof(char) * ft_count_chars(s, c, i) + 1);

// 		if (dst[j] == NULL)
// 			return (NULL);
// 		while (s[i] && s[i] != c)
// 		{
// 			dst[j][k++] = s[i++];
// 		}
// 		while (s[i] == c && s[i] && flag == 0)
// 			i++;
// 		dst[j][k] = '\0';
// 		j++;
// 	}
// 	dst[numstr] = NULL;
// 	return (dst);
// }

static int		count_string(const char *s)
{
	int		i;
	int		count;
	int flag;

	int simple_flag;
	int	space_flag;
	int	double_flag;
	
	simple_flag = 0;
	space_flag = 0;
	double_flag = 0;
	i = 0;
	count = 0;
	flag = 0;
	while (s[i])
	{
		if (s[i] == '\'' && double_flag == 0)
			simple_flag = 1;
		else if (s[i] == '"' && simple_flag == 0)
			double_flag = 1;
		else if (double_flag == 1 || simple_flag == 1)
		{
			if (double_flag == 1)
			{
				while (s[i] != '"')
					i++;
				double_flag = 0;
				if (double_flag == 0 && s[i+1] != ' ')
				{
					while (s[i] && s[i] != ' ')
						i++;
					count++;
				}
				else
					count++;
			}
			if (simple_flag == 1)
			{
				while (s[i] != '\'')
					i++;
				simple_flag = 0;
				if (simple_flag == 0 && s[i+1] != ' ')
				{
					while (s[i] && s[i] != ' ')
						i++;
					count++;
				}
				else
					count++;
			}
		}
		else
		{
			if (s[i] != ' ')
			{
				count++;
				while (s[i] != ' ' && s[i])
					i++;
				if (s[i] == '"' && s[i+1] != '\0')
					count++;
			}
		}
		i++;
	}
	return (count);
}

char	**cut_arg(const char *s)
{
	//char	**dst;
	int		numstr;

	if (!s)
		return (NULL);
	numstr = count_string(s);
	printf("Number: %d\n", numstr);
	//dst = malloc(sizeof(char *) * (numstr + 1));
	// if (!dst)
	// 	return (NULL);
	// return (ft_write_string(s, dst, numstr));
	return (NULL);
}
