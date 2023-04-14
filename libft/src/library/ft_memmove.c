/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:52:36 by cllovio           #+#    #+#             */
/*   Updated: 2022/11/14 09:13:26 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char		*vdest;
	const char	*vsrc;

	vdest = (char *)dest;
	vsrc = (const char *)src;
	if (vdest <= vsrc)
		ft_memcpy(dest, src, len);
	else
	{
		while (len > 0)
		{
			vdest[len - 1] = vsrc[len - 1];
			len--;
		}
	}
	return (dest);
}
