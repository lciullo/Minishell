/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:52:54 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/05 16:10:06 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*on ne regarde que token de 1*/

#include "minishell.h"

void	swap_nodes(t_env *current_node, t_env *next_node)
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

void	sort_in_alphabetic_order(t_env *head)
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
	return (0);
}

int	implement_export(char **token, t_exec *data, t_env *lst)
{
	char	*name;
	char	*value;

	name = NULL;
	value = NULL;
	(void)data;
	if (!token[1])
		print_export(lst);
	else if (token[1])
	{
		name = get_name_variable(token[1]);
		manage_export(token, data, lst);
	}
	return (0);
}
