/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:36:32 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/06 15:38:17 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap_nodes(t_env *current_node, t_env *next_node)
{
	char	*name;
	char	*value;

	name = NULL;
	value = NULL;
	name = current_node->name;
	current_node->name = next_node->name;
	next_node->name = name;
	value = current_node->value;
	current_node->value = next_node->value;
	next_node->value = value;
}

static void	sort_in_alphabetic_order(t_env *head)
{
	int		to_sort;
	t_env	*tmp;
	t_env	*end;

	if (head == NULL)
		return ;
	to_sort = 1;
	end = NULL;
	while (to_sort)
	{
		to_sort = 0;
		tmp = head;
		while (tmp->next != end)
		{
			if (ft_strcmp(tmp->name, tmp->next->name) > 0)
			{
				swap_nodes(tmp, tmp->next);
				to_sort = 1;
			}
			tmp = tmp->next;
		}
		end = tmp;
	}
	list_print_export(head);
}

int	print_export(t_env *lst)
{
	sort_in_alphabetic_order(lst);
	return (SUCCESS);
}
