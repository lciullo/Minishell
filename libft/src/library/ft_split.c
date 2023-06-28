/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisa <lisa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:39:18 by lciullo           #+#    #+#             */
/*   Updated: 2023/02/24 20:49:38 by lisa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_split(char **arr, size_t row)
{
	size_t	i;

	i = 0;
	while (i < row + 1)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return ;
}

size_t	nb_words(char const *s, char c)
{
	size_t	i;
	size_t	word;
	size_t	is_word;

	i = 0;
	word = 0;
	is_word = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && is_word == 0)
		{
			is_word = 1;
			word++;
		}
		else if (s[i] == c)
			is_word = 0;
		i++;
	}
	return (word);
}

static char	**make_row(char const *s, char c, char **tab, size_t row)
{
	size_t	start;
	size_t	i;

	i = 0;
	start = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] && s[i] != c)
				i++;
			tab[row] = ft_substr(s, start, i - start);
			if (!(tab[row]))
			{
				free_split(tab, row);
				return (NULL);
			}
			row++;
		}
		else
			i++;
	}
	tab[row] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	row;

	if (s)
	{
		row = 0;
		tab = malloc(sizeof(char *) * (nb_words(s, c) + 1));
		if (!tab)
			return (NULL);
		return (make_row(s, c, tab, row));
	}
	return (NULL);
}
