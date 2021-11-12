/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 19:23:22 by ldurante          #+#    #+#             */
/*   Updated: 2021/04/16 12:52:51 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_count_string(const char *s)
{
	int		count;
	int		i;
	char	c;
	int		flag;

	flag = 0;
	count = 0;
	c = ' ';
	i = 0;
	while(s[i])
	{
		if (s[i] == '"' && flag == 0)
		{
			flag = 1;
			c = '"';
		}
		else if (s[i] == '"' && flag == 1)
		{
			flag = 0;
			c = ' ';
			i++;
		}
		if (s[i] != c && s[i])
		{
			count++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		else if (s[i] != '\0')
			i++;
	}
	return (count);
}

static int	ft_count_chars(const char *s, char c, int i)
{
	int		counter;

	counter = 0;
	if (!s)
		return (0);
	while (s[i] != '\0' && s[i] != c)
	{
		counter++;
		i++;
	}
	return (counter);
}

static char	**ft_write_string(char const *s, char **dst, int numstr)
{
	int		i;
	int		j;
	int		k;
	char	c;
	int		flag;

	c = ' ';
	i = 0;
	j = 0;
	flag = 0;
	while (s[i] && j < numstr)
	{
		if (s[i] == '"' && flag == 0)
		{
			flag = 1;
			c = '"';
		}
		else if (s[i] == '"' && flag == 1)
		{
			flag = 0;
			c = ' ';
			i++;
		}
		k = 0;
		while (s[i] == c && s[i])
			i++;
		dst[j] = malloc(sizeof(char) * ft_count_chars(s, c, i) + 1);

		if (dst[j] == NULL)
			return (NULL);
		while (s[i] && s[i] != c)
		{
			dst[j][k++] = s[i++];
		}
		while (s[i] == c && s[i] && flag == 0)
			i++;
		dst[j][k] = '\0';
		j++;
	}
	dst[numstr] = NULL;
	return (dst);
}

char	**cut_arg(char const *s)
{
	char	**dst;
	int		numstr;

	if (!s)
		return (NULL);
	numstr = ft_count_string(s);
	dst = malloc(sizeof(char *) * (numstr + 1));
	if (!dst)
		return (NULL);
	return (ft_write_string(s, dst, numstr));
}
