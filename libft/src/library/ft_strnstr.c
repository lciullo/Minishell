/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:35:12 by lciullo           #+#    #+#             */
/*   Updated: 2023/03/14 10:18:25 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *search, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (ft_strlen(search) == 0)
		return ((char *)str);
	if (n == 0 || ft_strlen(str) == 0)
		return (NULL);
	if (ft_strlen(search) > ft_strlen(str))
		return (NULL);
	while (str[i] != '\0' && i < n)
	{
		if (str[i] == search[j])
			j++;
		else if (search[j] != '\0')
		{
			i = i - j;
			j = 0;
		}
		if (search[j] == '\0')
			return ((char *)&str[i - j + 1]);
		i++;
	}
	return (NULL);
}
