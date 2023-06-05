/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:52:54 by lciullo           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/06/05 10:25:58 by lciullo          ###   ########.fr       */
=======
/*   Updated: 2023/05/31 08:35:18 by lciullo          ###   ########.fr       */
>>>>>>> 96bc9bc364ecd1355a5ac1e35544a7d01ed3cc12
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//void	del_smallest(t_env **list, char *tmp_1);

<<<<<<< HEAD
void	swap_nodes(t_env *current_node, t_env *next_node)
=======
/*int	print_export(t_env **lst)
>>>>>>> 96bc9bc364ecd1355a5ac1e35544a7d01ed3cc12
{
	char	*name;
	char	*value;

<<<<<<< HEAD
	name = NULL;
	value = NULL;
	name = current_node->name;
	current_node->name = next_node->name;
	next_node->name = name;
	value = current_node->value;
	current_node->value = next_node->value;
	next_node->value = value;
=======
	(void)tmp_2;
	temp = (*lst);
	nbr_node = 0;
	i = 0;
	while (temp)
	{
		nbr_node++;
		temp = temp->next;
	}
	temp = (*lst);
	tmp_1 = ft_strdup((*lst)->name);
	tmp_2 = ft_strdup((*lst)->value);
	head = temp;
	(void)head;
	while (i < nbr_node)
	{
		tmp_1 = ft_strdup(temp->name);
		tmp_2 = ft_strdup(temp->value);
		while (temp)
		{
			if (ft_strcmp(tmp_1, temp->name) > 0)
			{
				free(tmp_1);
				free(tmp_2);
				tmp_1 = ft_strdup(temp->name);
				tmp_2 = ft_strdup(temp->value);
			}
			temp = temp->next;
		}
		temp = head;
		del_smallest(&temp, tmp_1);
		ft_dprintf(1, "%s = %s\n", tmp_1, tmp_2);
		i++;
	}
	return (0);
}*/

/*void	del_smallest(t_env **list, char *tmp_1)
{
	t_env	*copy;

	if (*list == NULL || list == NULL)
		return ;
	copy = (*list);
	if (ft_strcmp(copy->name, tmp_1) == 0)
	{
		*list = copy->next;
		free(copy->name);
		free(copy->value);
		free(copy);
		del_smallest(list, tmp_1);
	}
	copy = *list;
	del_smallest(&copy->next, tmp_1);
}*/

void	swap_nodes(t_env *a, t_env *b)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = a->name;
	a->name = b->name;
	b->name = tmp1;
	tmp2 = a->value;
	a->value = b->value;
	b->value = tmp2;
>>>>>>> 96bc9bc364ecd1355a5ac1e35544a7d01ed3cc12
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
<<<<<<< HEAD

int	print_export(t_env *lst_env)
=======
int	print_export(t_env *lst)
>>>>>>> 96bc9bc364ecd1355a5ac1e35544a7d01ed3cc12
{
	sort_in_alphabetic_order(lst);
	return (0);
}

int	implement_export(char **token, t_exec *data, t_env *lst)
{
	(void)data;
	if (!token[1])
		print_export(lst);
	return (0);
}
