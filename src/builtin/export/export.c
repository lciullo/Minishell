/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:52:54 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/09 09:03:01 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*on ne regarde que token de 1*/
//si ya des leaks tmp 
//fixe le += plus tard name-1 boucler sur les arguments
/*void	print_print(t_env *lst)
{
	t_env	*copy;

	copy = lst;
	while (copy)
	{
		ft_dprintf(1, "[%s] =  [%s]\n", copy->name, copy->value);
		ft_dprintf(1, "%d\n", copy->equal);
		copy = copy->next;
	}
}*/

#include "minishell.h"

int	is_in_env(t_env *lst, char *name)
{
	char	*to_find;

	to_find = remove_plus_in_name(name);
	if (!to_find)
		return (FAILURE);
	while (lst != NULL)
	{
		if (ft_strcmp(lst->name, to_find) == 0)
			return (SUCCESS);
		lst = lst->next;
	}
	return (FAILURE);
}

int	add_to_export(t_env **lst, char *name, char *value, char *to_find)
{
	(void)value;
	if (is_equal(to_find) == EQUAL)
	{
		if (is_in_env(*lst, name) == SUCCESS)
			search_and_replace_value(*lst, name, value);
		else
			*lst = add_back_with_equal(*lst, name, value);
	}
	else
	{
		if (is_in_env(*lst, name) == FAILURE)
		{
			ft_lstadd_back_env(lst, ft_lstnew_env(name, value));
			change_equal_to_zero(*lst, name);
		}
	}
	return (SUCCESS);
}

static int	loop_for_export_arguments(char **token, t_env **lst)
{
	char	*name;
	char	*value;
	char	*to_find;
	int		i;

	name = NULL;
	value = NULL;
	to_find = NULL;
	i = 1;
	while (token[i])
	{
		name = get_name_variable(token[i]);
		to_find = get_name_variable(token[i]);
		if (parse_name(name) == FAILURE)
			return (FAILURE);
		if (is_equal(token[i]) == EQUAL)
			value = get_value_variable(token[i]);
		add_to_export(lst, name, value, token[i]);
		if (value)
			free(value);
		free(to_find);
		i++;
	}
	return (SUCCESS);
}

int	implement_export(char **token, t_env **lst)
{
	if (!token[1])
		print_export(*lst);
	else if (token[1][0] == '-')
	{
		ft_dprintf(2, "Invalid option, subject : export with no options\n");
		return (FAILURE);
	}
	else if (token[1][0] != '-')
	{
		if (loop_for_export_arguments(token, lst) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
