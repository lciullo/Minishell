/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 09:21:23 by cllovio           #+#    #+#             */
/*   Updated: 2023/06/22 14:21:34 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*delete_quote(char *row);
static int	get_nbr_quote(char *row);
static void	copy_quote_content(char *new_s, char *row, int *i, int *j);

char	*is_there_a_quote(char *row)
{
	int		i;

	i = 0;
	while (row[i])
	{
		if (row[i] == '\'' || row[i] == '\"')
		{
			row = delete_quote(row);
			if (!row)
				return (NULL);
			break ;
		}
		i++;
	}
	return (row);
}

static char	*delete_quote(char *row)
{
	int		i;
	int		j;
	char	*new_s;

	new_s = malloc(sizeof(char) * \
	(ft_strlen(row) - (get_nbr_quote(row) * 1) + 1));
	if (!new_s)
		return (NULL);
	i = 0;
	j = 0;
	while (row[i])
	{
		if (row[i] == '\'' || row[i] == '\"')
			copy_quote_content(new_s, row, &i, &j);
		else
		{
			new_s[j] = row[i];
			i++;
			j++;
		}
	}
	new_s[j] = '\0';
	free(row);
	return (new_s);
}

static int	get_nbr_quote(char *row)
{
	int		nbr_quote;
	int		i;
	char	quote;

	nbr_quote = 0;
	i = 0;
	while (row[i])
	{
		if (row[i] == '\'' || row[i] == '\"')
		{
			quote = row[i];
			nbr_quote++;
			while (row[++i])
			{
				if (row[i] == quote)
				{
					i++;
					break ;
				}
			}
		}
		else
			i++;
	}
	return (nbr_quote);
}

static void	copy_quote_content(char *new_s, char *row, int *i, int *j)
{
	char	quote;

	quote = row[*i];
	*i = *i + 1;
	while (row[*i])
	{
		if (row[*i] == quote)
		{
			*i = *i + 1;
			break ;
		}
		else
		{
			new_s[*j] = row[*i];
			*i = *i + 1;
			*j = *j + 1;
		}
	}
}
