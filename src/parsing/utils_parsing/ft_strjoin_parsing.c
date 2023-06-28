/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_parsing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 14:39:19 by cllovio           #+#    #+#             */
/*   Updated: 2023/06/25 14:39:21 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_parsing(char *s1, char *s2)
{
	char	*str;
	int		j;
	int		i;

	j = 0;
	i = 0;
	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (free(s1), NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (free(s1), str);
}

char	*ft_strjoin_expand(char*s1, char *s2, int start, int i)
{
	int		j;
	char	*new_s;

	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	new_s = malloc(sizeof(char) * (ft_strlen(s1) + (i - start) + 1));
	if (!(new_s))
		return (free(s1), NULL);
	while (s1[j])
	{
		new_s[j] = s1[j];
		j++;
	}
	while (start < i)
	{
		new_s[j] = s2[start];
		j++;
		start++;
	}
	new_s[j] = '\0';
	return (new_s);
}
