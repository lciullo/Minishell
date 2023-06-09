/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:52:54 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/09 17:00:20 by lciullo          ###   ########.fr       */
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
	int	no_env;
	int	in_env;

	no_env = 0;
	in_env = 1;
	if (is_equal(to_find) == EQUAL)
	{
		if (in_env == 1)
			search_and_replace_value(*lst, name, value);
		else
			*lst = add_back_with_equal(*lst, name, value);
	}
	else
	{
		if (no_env == 0)
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
	int		in_env;
	int		i;

	name = NULL;
	value = NULL;
	in_env = 0;
	i = 1;
	while (token[i])
	{
		if (is_in_env(*lst, "USER") == SUCCESS)
			in_env = 1;
		name = get_name_variable(token[i]);
		if (parse_name(name) == FAILURE)
			return (FAILURE);
		if (is_equal(token[i]) == EQUAL)
			value = get_value_variable(token[i]);
		add_to_export(lst, name, value, token[i]);
		if ((is_equal(token[i]) == NO_EQUAL) && in_env == 1)
		{
			//USER | OUI
			free(name);
		}
		else if ((is_equal(token[i]) == EQUAL) && in_env == 1)
		{
			free(name);
			free(value);
		}
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
