/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:20:13 by cllovio           #+#    #+#             */
/*   Updated: 2022/11/22 16:26:55 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	get_last_set(char const *s1, char const *set)
{
	int	len;

	len = ft_strlen(s1);
	while (len >= 0 && get_set(s1[len - 1], set) == 1)
		len--;
	return (len);
}

static int	get_first_set(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (get_set(s1[i], set) == 1)
		i++;
	return (i);
}

static int	len_new_s(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = get_first_set(s1, set);
	k = get_last_set(s1, set);
	while (s1[j] && j < k)
	{
		i++;
		j++;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		k;
	char	*new_s;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = get_first_set(s1, set);
	k = get_last_set(s1, set);
	new_s = malloc(sizeof(char) * (len_new_s(s1, set) + 1));
	if (!(new_s))
		return (NULL);
	while (j < k)
	{
		new_s[i] = s1[j];
		i++;
		j++;
	}
	new_s[i] = '\0';
	return (new_s);
}
