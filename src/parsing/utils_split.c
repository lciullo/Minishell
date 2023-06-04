/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:51:27 by cllovio           #+#    #+#             */
/*   Updated: 2023/06/04 12:39:07 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_white_space(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (true);
	return (false);
}

bool	check_character(char c, int type)
{
	if (type == 0 && c != '>' && c != '<' && c != '|' && c != '\'' && c != '\"')
		return (true);
	if (type == 1 && (c == '>' || c == '<' || c == '|'))
		return (true);
	if (type == 2 && (c != '>' && c != '<' && c != '|'))
		return (true);
	return (false);
}

void	check_sep(char *line, int *i, int *nb_words)
{
	if (line[*i] && (line[*i] == '|' || line[*i] == '<' || line[*i] == '>'))
	{
		*nb_words = *nb_words + 1;
		*i = *i + 1;
		if (line[*i] == '<' || line[*i] == '>')
			i++;
	}
	if (line[*i] == '\'' || line[*i] == '\"')
	{
		skip_quote(line, i, line[*i]);
		*nb_words = *nb_words + 1;
	}
}

void	*ft_free_parsing(char **tab, int j)
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
