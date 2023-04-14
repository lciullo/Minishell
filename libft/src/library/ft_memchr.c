/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 09:39:28 by cllovio           #+#    #+#             */
/*   Updated: 2022/11/12 14:30:50 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	character;
	unsigned char	*string;
	size_t			i;

	character = (unsigned char) c;
	string = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (string[i] == character)
			return (&string[i]);
		i++;
	}
	return (0);
}
