/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:59:26 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/08 17:29:24 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_plus_in_name(char *name)
{
	char	*to_find;

	to_find = NULL;
	if (last_char(name) == PLUS)
	{
		to_find = ft_strndup(to_find, name, (unsigned int)ft_strlen(name) - 1);
		if (!to_find)
			return (NULL);
		return (to_find);
	}
	return (name);
}

char	*get_name_variable(char *row)
{
	char		*name;
	size_t		start;

	name = NULL;
	start = begin_of_name(row);
	name = ft_strndup(name, row, start);
	if (!name)
		return (NULL);
	return (name);
}

char	*get_value_variable(char *row)
{
	size_t		start;
	char		*value;

	value = NULL;
	start = begin_of_name(row);
	value = ft_strndup(value, &row[start + 1], ft_strlen(row));
	if (!value)
		return (NULL);
	return (value);
}

void	change_equal_to_one(t_env *lst, char *name)
{
	while (lst != NULL)
	{
		if ((ft_strcmp(lst->name, name) == 0))
		{
			if (lst->equal == 0)
				lst->equal = 1;
		}
		lst = lst->next;
	}
}

void	change_equal_to_zero(t_env *lst, char *name)
{
	while (lst != NULL)
	{
		if ((ft_strcmp(lst->name, name) == 0))
		{
			if (lst->equal == 1)
				lst->equal = 0;
		}
		lst = lst->next;
	}
}
