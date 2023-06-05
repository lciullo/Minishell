/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:52:54 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/05 10:25:58 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//void	del_smallest(t_env **list, char *tmp_1);

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
	list_print_env(head);
}

int	print_export(t_env *lst_env)
{
	sort_in_alphabetic_order(lst_env);
	return (0);
}

int	implement_export(char **token, t_exec *data, t_env *lst_env)
{
	(void)data;
	if (!token[1])
		print_export(lst_env);
	return (0);
}
