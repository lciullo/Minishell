/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_order.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:22:13 by cllovio           #+#    #+#             */
/*   Updated: 2023/06/06 09:24:01 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_tab_size(char **tab);
static void	change_order_redir(char **tab, \
			char **new_tab, t_data *data, int *i);
static void	change_order_token(char **tab, char **new_tab, \
			t_data *data, int *i);

char	**change_order(char **tab, t_data *data)
{
	char	**new_tab;
	int		i;

	i = 0;
	new_tab = malloc(sizeof(char *) * (get_tab_size(tab) + 1));
	if (!new_tab)
		return (NULL);
	while (tab[data->end])
	{
		if (tab[data->end][0] == '|' || tab[data->end + 1] == NULL)
			change_order_redir(tab, new_tab, data, &i);
		data->end++;
	}
	new_tab[data->end] = NULL;
	free_array(tab);
	return (new_tab);
}

static int	get_tab_size(char **tab)
{
	int	tab_size;

	tab_size = 0;
	while (tab[tab_size])
		tab_size++;
	return (tab_size);
}

static void	change_order_redir(char **tab, char **new_tab, t_data *data, int *i)
{
	int	start_b;

	start_b = data->start;
	while (data->start < data->end)
	{
		if (tab[data->start][0] == '<' || tab[data->start][0] == '>')
		{
			new_tab[*i] = ft_strdup(tab[data->start]);
			*i = *i + 1;
			data->start++;
			new_tab[*i] = ft_strdup(tab[data->start]);
			*i = *i + 1;
		}
		data->start++;
	}
	data->start = start_b;
	change_order_token(tab, new_tab, data, i);
}

static void	change_order_token(char **tab, char **new_tab, t_data *data, int *i)
{
	while (data->start <= data->end)
	{
		if (tab[data->start][0] == '<' || tab[data->start][0] == '>')
			data->start++;
		if (data->start > 0 && (tab[data->start - 1][0] == '<' \
		|| tab[data->start - 1][0] == '>'))
			data->start++;
		else
		{
			new_tab[*i] = ft_strdup(tab[data->start]);
			*i = *i + 1;
			data->start++;
		}
	}
	data->start = data->end + 1;
}
