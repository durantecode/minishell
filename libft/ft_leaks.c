/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_leaks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 21:35:12 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/18 21:35:35 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_leaks(char *str)
{
	char	*full_name;

	full_name = ft_strjoin("leaks -q ", str);
	system(full_name);
	free(full_name);
}
