/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 08:38:25 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/03 13:54:30 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	dest = malloc(sizeof(char) * n + 1);
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

// char	*ft_strdup(const char *s)
// {
// 	unsigned int	i;
// 	char	*new_s;
	
// 	i = 0;
// 	while (s[i])
// 		i++;
// 	new_s = malloc(sizeof(char) * (i + 1));
// 	if (!new_s)
// 		return (NULL);
// 	i = 0;
// 	while (s[i])
// 	{
// 		new_s[i] = s[i];
// 		i++;
// 	}
// 	new_s[i] = '\0';
// 	return (new_s);
// }