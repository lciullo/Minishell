/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:43:32 by cllovio           #+#    #+#             */
/*   Updated: 2023/05/30 09:05:06 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*split_separator(char *line, size_t *i);
char	*split_word(char *line, size_t *i);

static int	ft_count_words_parsing(char *s)
{
	int	i;
	int	nb_words;
	int	is_valid;

	i = 0;
	nb_words = 0;
	while (s[i])
	{
		is_valid = 0;
		while (s[i] && is_white_space(s[i]) == true)
			i++;
		check_separator(s, &i, &nb_words);
		while (s[i] && is_white_space(s[i]) == false \
		&& check_character(s[i], 0))
		{
			is_valid = 1;
			i++;
		}
		if ((s[i] == 0 || is_white_space(s[i]) == true || \
		check_character(s[i], 1)) && is_valid)
			nb_words++;
	}
	//printf("nb_words : %d\n", nb_words);
	return (nb_words);
}

static char	**ft_sp_parsing(char *s, char **tab, size_t i)
{
	size_t		j;

	j = 0;
	while (s[i])
	{
		if (s[i] == '|' || s[i] == '<' || s[i] == '>')
		{
			tab[j] = split_separator(s, &i);
			if (!(tab[j]))
				return (ft_free_parsing(tab, j), NULL);
			j++;
		}
		if (s[i] && is_white_space(s[i]) == false)
		{
			tab[j] = split_word(s, &i);
			if (!(tab[j]))
				return (ft_free_parsing(tab, j), NULL);
			j++;
		}
		else
			i++;
	}
	tab[j] = NULL;
	return (tab);
}

char	*split_word(char *line, size_t *i)
{
	size_t	start;
	char	*row;

	start = *i;
	while (line[*i] && is_white_space(line[*i]) == false \
	&& check_character(line[*i], 2) == true)
	{
		if (line[*i] == '\'' || line[*i] == '\"')
			skip_quote(line, (int *)i, line[*i]);
		if (line[*i] == '|' || line[*i] == '>' || line[*i] == '<')
			break ;
		if (line[*i])
			*i = *i + 1;
	}
	row = ft_substr(line, start, (int)(*i - start));
	return (row);
}

char	*split_separator(char *line, size_t *i)
{
	char	*row;

	if (line[*i] == '|')
	{
		row = ft_substr(line, *i, 1);
		*i = *i + 1;
	}
	else if (line[*i] == '>' || line[*i] == '<')
	{
		if (line[*i + 1] && (line[*i + 1] == '>' || line[*i + 1] == '<'))
		{
			row = ft_substr(line, *i, 2);
			*i = *i + 1;
		}
		else
			row = ft_substr(line, *i, 1);
		*i = *i + 1;
	}
	return (row);
}

char	**ft_split_parsing(char *s)
{
	char		**tab;

	tab = malloc(sizeof(char *) * (ft_count_words_parsing(s) + 1));
	if (!(tab) || !(s))
		return (NULL);
	return (ft_sp_parsing(s, tab, 0));
}
