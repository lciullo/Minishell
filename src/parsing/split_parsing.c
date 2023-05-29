/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:43:32 by cllovio           #+#    #+#             */
/*   Updated: 2023/05/29 15:45:43 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_white_space(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (true);
	return (false);
}

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
		if (s[i] && (s[i] == '|' || s[i] == '<' || s[i] == '>'))
		{
			nb_words++;
			i++;
			if (s[i] == '<' || s[i] == '>')
				i++;
		}
		if (s[i] == '\''  || s[i] == '\"')
		{
			skip_quote(s, &i, s[i]);
			nb_words++;
		}
		while (s[i] && is_white_space(s[i]) == false && s[i] != '>' && s[i] != '<' && s[i] != '|' && s[i] != '\'' && s[i] != '\"')
		{
			is_valid = 1;
			i++;
		}
		if ((s[i] == 0 || is_white_space(s[i]) == true || s[i] == '>' || s[i] == '<' || s[i] == '|') && is_valid)
			nb_words++;
	}
	ft_dprintf(2, "nb_words : %d\n", nb_words);
	return (nb_words);
}

static void	*ft_free_parsing(char **tab, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static char	**ft_sp_parsing(char *s, char **tab)
{
	size_t		i;
	size_t		j;
	size_t		start;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '|')
		{
			tab[j] = ft_substr(s, i, 1);
			i++;
			j++;
		}
		if (s[i] && (s[i] == '>' || s[i] == '<'))
		{
			if (s[i + 1] && (s[i + 1] == '>' || s[i + 1] == '<'))
			{
				tab[j] = ft_substr(s, i, 2);
				i++;
			}
			else
				tab[j] = ft_substr(s, i, 1);
			i++;
			j++;
		}
		if (is_white_space(s[i]) == false)
		{
			start = i;
			while (s[i] && is_white_space(s[i]) == false && s[i] != '>' && s[i] != '<' && s[i] != '|')
				i++;
			tab[j] = ft_substr(s, start, i - start);
			if (!(tab[j]))
				return (ft_free_parsing(tab, j));
			j++;
		}
		else
			i++;
	}
	tab[j] = NULL;
	print_tab(tab);
	return (tab);
}

char	**ft_split_parsing(char *s)
{
	char		**tab;

	tab = malloc(sizeof(char *) * (ft_count_words_parsing(s) + 1));
	if (!(tab) || !(s))
		return (NULL);
	return (ft_sp_parsing(s, tab));
}
