/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:57:52 by lciullo           #+#    #+#             */
/*   Updated: 2023/04/18 16:03:20 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	next_line_len(char *buffer)
{
	unsigned int	i;

	i = 0;
	while (buffer[i] != '\n')
	{
		if (buffer[i] == '\0')
		{
			return (i);
		}
		i++;
	}
	return (i);
}

char	*gnl_join(char *s1, char *s2)
{
	int		i;
	int		pos;
	char	*tab;

	if (!s1)
		return (NULL);
	if (!s2)
	{
		free(s1);
		return (NULL);
	}
	tab = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!(tab))
		return (NULL);
	i = 0;
	pos = 0;
	while (s1[i] != '\0')
		tab[pos++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		tab[pos++] = s2[i++];
	tab[pos] = '\0';
	free(s1);
	free(s2);
	return (tab);
}
