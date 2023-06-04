/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_order.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:22:13 by cllovio           #+#    #+#             */
/*   Updated: 2023/05/30 14:39:43 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**change_order(char **tab)
{
	int		tab_size;
	char	**new_tab;
	int		end;
	int		start;
	int		i;

	tab_size = 0;
	end = 0;
	start = 0;
	i = 0;
	while (tab[tab_size])
		tab_size++;
	new_tab = malloc(sizeof(char *) * (tab_size + 1));
	if (!new_tab)
		return (NULL);
	while (tab[end])
	{
		if (tab[end][0] == '|' || tab[end + 1] == NULL)
		{
			change_order_redir(new_tab, tab, start, end, &i);
			start = end + 1;
		}
		end++;
	}
	new_tab[end] = NULL;
	free_array(tab);
	return (new_tab);
}

void	change_order_redir(char **new_tab, char **tab, \
int start, int end, int *i)
{
	int	start_b;

	start_b = start;
	while (start < end)
	{
		if (tab[start][0] == '<' || tab[start][0] == '>')
		{
			new_tab[*i] = ft_strdup(tab[start]);
			*i = *i + 1;
			start++;
			new_tab[*i] = ft_strdup(tab[start]);
			*i = *i + 1;
		}
		start++;
	}
	change_order_token(new_tab, tab, start_b, end, i);
}

void	change_order_token(char **new_tab, char **tab, \
int start, int end, int *i)
{
	while (start <= end)
	{
		if (tab[start][0] == '<' || tab[start][0] == '>')
			start++;
		if (start > 0 && (tab[start - 1][0] == '<' || tab[start - 1][0] == '>'))
			start++;
		else
		{
			new_tab[*i] = ft_strdup(tab[start]);
			*i = *i + 1;
			start++;
		}
	}
}
