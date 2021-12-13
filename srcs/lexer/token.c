/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:43:03 by ldurante          #+#    #+#             */
/*   Updated: 2021/12/13 21:14:23 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	double_quotes(t_input *in, const char *s)
{
	while (s[in->flags.i] != '"' && s[in->flags.i] != '\0')
		in->flags.i++;
	in->flags.double_q = 0;
	if (!in->flags.double_q && s[in->flags.i + 1] != ' ')
	{
		while (s[in->flags.i] && s[in->flags.i] != ' ')
			in->flags.i++;
		in->flags.count++;
		in->flags.global_count = 1;
	}
	else
	{
		in->flags.count++;
		in->flags.global_count = 1;
	}
}

void	single_quotes(t_input *in, const char *s)
{
	while (s[in->flags.i] != '\'' && s[in->flags.i] != '\0')
		in->flags.i++;
	in->flags.single_q = 0;
	if (!in->flags.single_q && s[in->flags.i + 1] != ' ')
	{
		while (s[in->flags.i] && s[in->flags.i] != ' ')
			in->flags.i++;
		in->flags.count++;
		in->flags.global_count = 1;
	}
	else
	{
		in->flags.count++;
		in->flags.global_count = 1;
	}
}

void	split_args(t_input *in, const char *s)
{
	if (!in->flags.global_q)
	{
		if (s[in->flags.i - 1] != ' ')
			in->split_input[in->flags.j] = ft_substr(s, in->flags.start,
					in->flags.i - in->flags.start);
		else
			in->split_input[in->flags.j] = ft_substr(s, in->flags.start,
					in->flags.i - in->flags.start - 1);
	}
	else if (in->flags.global_sp)
	{
		in->split_input[in->flags.j] = ft_substr(s, in->flags.start,
				in->flags.i - in->flags.start);
		in->flags.global_sp = 0;
		in->flags.global_q = 0;
	}	
	if (in->split_input[in->flags.j])
		in->flags.j++;
	in->flags.global_count = 0;
}

void	token_aux(t_input *in, const char *s, int split, int n)
{
	if (n == 0)
	{
		if (s[in->flags.i] != ' ' && s[in->flags.i] != '\0')
		{
			in->flags.count++;
			while (s[in->flags.i] != ' ' && s[in->flags.i])
				in->flags.i++;
			in->flags.global_count = 1;
		}
	}
	if (n == 1)
	{
		if (s[in->flags.i])
			in->flags.i++;
		if (split == 1 && in->flags.global_count)
			split_args(in, s);
		if (!in->flags.global_q)
			in->flags.start = in->flags.i;
	}
}

void	check_errors_aux2(t_input *in)
{
	if (in->user_input[in->flags.i] == '"' && !in->flags.single_q
		&& !in->flags.double_q)
	{
		in->flags.double_q = 1;
	}
	else if (in->user_input[in->flags.i] == '"' && !in->flags.single_q
		&& in->flags.double_q)
	{
		in->flags.double_q = 0;
	}
	else if (in->user_input[in->flags.i] == '\'' && !in->flags.single_q
		&& !in->flags.double_q)
	{
		in->flags.single_q = 1;
	}
	else if (in->user_input[in->flags.i] == '\'' && in->flags.single_q
		&& !in->flags.double_q)
	{
		in->flags.single_q = 0;
	}
}

int	count_tokens(const char *s, t_input *in, int split)
{
	int prov;
	int	j;

	j = 0;
	prov = 0;
	while (s[in->flags.i] != '\0')
	{
		check_errors_aux2(in);
		if (!in->flags.double_q && !in->flags.single_q && s[in->flags.i] != '\'' && s[in->flags.i] != '"')
		{
			printf("|%c|\n", s[in->flags.i]);
			printf("%d\n", in->flags.i);
			printf("|%c|\n\n", s[in->flags.i-1]);
			while (s[in->flags.i] && s[in->flags.i] != ' ' && s[in->flags.i] != '\'' && s[in->flags.i] != '"')
			{
				in->flags.i++;
			}
			if (!s[in->flags.i] && prov == 0)
				in->flags.count++;
			if(s[in->flags.i] == ' ')
			{
				in->flags.count++;
				prov = 0;
				while(s[in->flags.i] == ' ' && s[in->flags.i])
				{
					in->flags.i++;
				}
			}
			else if (s[in->flags.i] != '\'' && s[in->flags.i] != '"' && s[in->flags.i])
				in->flags.i++;
		}
		else if (in->flags.double_q || in->flags.single_q)
		{
			printf("VUELTA2\n");
			if (s[in->flags.i - 1] == ' ' && (s[in->flags.i] == '"' || s[in->flags.i] == '\''))
			{
				if (in->flags.double_q)
				{
					while (in->flags.double_q)
					{
						check_errors_aux2(in);
						in->flags.i++;
					}
					if (s[in->flags.i] == ' ' || s[in->flags.i] == '\0')
					{
						in->flags.count++;
						prov = 1;
					}
				}
				else if (in->flags.single_q)
				{
					while (in->flags.single_q)
					{
						check_errors_aux2(in);
						in->flags.i++;
					}

					printf("-%c-\n", s[in->flags.i]);
					printf("-%c-\n\n", s[in->flags.i-1]);
					if (s[in->flags.i + 1] == ' ' || s[in->flags.i + 1] == '\0')
					{
						in->flags.count++;
						prov = 1;
					}
				}
			}
			if (!s[in->flags.i])
				in->flags.count++;
			in->flags.i++;
		}
	}
	// if (split == 1)
	// {
	// 	in->flags.i = 0;
	// 	in->flags.start = 0;
	// 	while (s[in->flags.i] != '\0')
	// 	{
	// 		check_errors_aux2(in);
	// 		if (!in->flags.double_q && !in->flags.single_q && s[in->flags.i] != '\'' && s[in->flags.i] != '"')
	// 		{
	// 			while (s[in->flags.i] && s[in->flags.i] != ' ' && s[in->flags.i] != '\'' && s[in->flags.i] != '"')
	// 			{
	// 				in->flags.i++;
	// 			}
	// 			if (!s[in->flags.i] && prov == 0)
	// 			{
	// 				in->split_input[j] = ft_substr(s, in->flags.start, in->flags.i - in->flags.start);
	// 				in->flags.start = in->flags.i;
	// 				j++;
	// 			}
	// 			if(s[in->flags.i] == ' ')
	// 			{
	// 				prov = 0;
	// 				in->split_input[j] = ft_substr(s, in->flags.start, in->flags.i - in->flags.start);
	// 				in->flags.start = in->flags.i;
	// 				j++;
	// 				while(s[in->flags.i] == ' ' && s[in->flags.i])
	// 				{
	// 					in->flags.i++;
	// 				}
	// 			}
	// 			else if (s[in->flags.i] != '\'' && s[in->flags.i] != '"' && s[in->flags.i])
	// 				in->flags.i++;
	// 		}
	// 		else
	// 		{
				
	// 			if (s[in->flags.i - 1] == ' ' && (s[in->flags.i] == '"' || s[in->flags.i] == '\''))
	// 			{
	// 				if (s[in->flags.i] == '"' && in->flags.double_q)
	// 				{
	// 					in->split_input[j] = ft_substr(s, in->flags.start, in->flags.i - in->flags.start);
	// 					in->flags.start = in->flags.i;
	// 					j++;
	// 					prov = 1;
	// 				}
	// 				else if (s[in->flags.i] == '\'' && in->flags.single_q)
	// 				{
	// 					in->split_input[j] = ft_substr(s, in->flags.start, in->flags.i - in->flags.start);
	// 					in->flags.start = in->flags.i;
	// 					j++;
	// 					prov = 1;
	// 				}
	// 			}
	// 			in->flags.i++;
	// 		}
	// 	}
	// }
	(void)split;
		// 	if (n == 0)
		// {
		// 	if (s[in->flags.i] != ' ' && s[in->flags.i] != '\0')
		// 	{
		// 		in->flags.count++;
		// 		while (s[in->flags.i] != ' ' && s[in->flags.i])
		// 			in->flags.i++;
		// 		in->flags.global_count = 1;
		// 	}
		// }
		// if (n == 1)
		// {
		// 	if (s[in->flags.i])
		// 		in->flags.i++;
		// 	if (split == 1 && in->flags.global_count)
		// 		split_args(in, s);
		// 	if (!in->flags.global_q)
		// 		in->flags.start = in->flags.i;
		// }
	return (in->flags.count);
}



		// check_errors_aux(in);
		// if (s[in->flags.i] != '\'' && s[in->flags.i] != '"' && in->flags.double_q == 0 && in->flags.single_q == 0)
		// {
		// 	in->flags.count++;
		// 	while (s[in->flags.i] != ' ' && s[in->flags.i])
		// 		in->flags.i++;
		// 	while (s[in->flags.i] == ' ' && s[in->flags.i])
		// 		in->flags.i++;
		// }
		// else if (s[in->flags.i] == '\'' && in->flags.single_q == 1)
		// {
		// 	in->flags.count++;
		// 	while (s[in->flags.i] != '\'' && s[in->flags.i])
		// 		in->flags.i++;
		// }
		// else if (s[in->flags.i] == '"' && in->flags.double_q == 1)
		// {
		// 	in->flags.count++;
		// 	while (s[in->flags.i] != '"' && s[in->flags.i])
		// 		in->flags.i++;
		// }
		// else
		// 	in->flags.i++;