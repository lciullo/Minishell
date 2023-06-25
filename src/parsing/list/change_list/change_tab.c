/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 14:37:08 by cllovio           #+#    #+#             */
/*   Updated: 2023/06/25 14:37:10 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	reput_space(char **tab_line, int *i, int *j);

void	change_tab(char **tab_line, int type)
{
	int		i;
	int		j;

	i = 0;
	while (tab_line[i])
	{
		j = 0;
		if (type == 2)
			change_quote(tab_line[i], 1);
		else
		{
			while (tab_line[i][j])
			{
				if ((tab_line[i][j] == '\'' || \
				tab_line[i][j] == '\"') && type == 0)
					replace_space(tab_line[i], 0);
				else if ((tab_line[i][j] == '\'' || \
				tab_line[i][j] == '\"') && type == 1)
					reput_space(tab_line, &i, &j);
				if (tab_line[i][j] != '\0')
					j++;
			}
		}
		i++;
	}
}

void	replace_space(char *line, int i)
{
	int		check_quote;
	char	quote;

	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			check_quote = 0;
			quote = line[i];
			while (line[++i] && check_quote == 0)
			{
				if (line[i] == quote)
				{
					check_quote = 1;
					break ;
				}
				else if (line[i] == ' ')
					line[i] = -1;
			}
		}
		if (line[i] != '\0')
			i++;
	}
}

static void	reput_space(char **tab_line, int *i, int *j)
{
	char	quote;

	quote = tab_line[*i][*j];
	*j = *j + 1;
	while (tab_line[*i][*j])
	{
		if (tab_line[*i][*j] == quote)
			break ;
		if (tab_line[*i][*j] == -1)
			tab_line[*i][*j] = ' ';
		*j = *j + 1;
	}
}
