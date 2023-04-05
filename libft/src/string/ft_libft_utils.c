/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libft_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisa <lisa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 15:02:18 by lciullo           #+#    #+#             */
/*   Updated: 2023/03/16 18:08:57 by lisa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *src)
{
	int		len;
	int		i;
	char	*str_cpy;

	if (!src)
		return (NULL);
	i = 0;
	len = ft_strlen(src);
	str_cpy = malloc(sizeof(char) * (len + 1));
	if (str_cpy == NULL)
		return (0);
	while (src[i] != '\0' && i <= len)
	{
		str_cpy[i] = src[i];
		i++;
	}
	str_cpy[i] = '\0';
	return (str_cpy);
}

static	char	*ft_copy(const char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (ft_strlen(&s[start]) > len)
		str = malloc(sizeof(char) * (len + 1));
	else
		str = malloc(sizeof(char) * (ft_strlen(&s[start]) + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (i < start)
		i++;
	while (s[i] != '\0' && j < len)
	{
		str[j] = s[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	return (ft_copy(s, start, len));
}
