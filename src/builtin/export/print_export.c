/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:36:32 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/11 15:49:59 by lciullo          ###   ########.fr       */
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
}

static t_env	*copy_env_lst(t_env *lst)
{
	t_env	*node;
	t_env	*copy_env;

	node = NULL;
	copy_env = NULL;
	if (!lst)
		return (NULL);
	while (lst != NULL)
	{
		if (lst->value)
			node = ft_lstnew_env(ft_strdup(lst->name), ft_strdup(lst->value));
		else
			node = ft_lstnew_env(ft_strdup(lst->name), lst->value);
		if (!node)
		{
			ft_lstclear_env(&copy_env, free);
			return (NULL);
		}
		ft_lstadd_back_env(&copy_env, node);
		lst = lst->next;
	}
	return (copy_env);
}

int	print_export(t_env *lst)
{
	t_env	*copy_env;

	copy_env = NULL;
	copy_env = copy_env_lst(lst);
	if (!copy_env)
		return (FAILURE);
	sort_in_alphabetic_order(copy_env);
	list_print_export(copy_env);
	ft_lstclear_env(&copy_env, free);
	return (SUCCESS);
}
