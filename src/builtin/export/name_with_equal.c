/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_with_equal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:08:52 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/09 16:36:31 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_and_replace_value(t_env *lst, char *name, char *value)
{
	char	*to_find;
	char	*temp;

	to_find = remove_plus_in_name(name);
	if (!to_find)
		return (FAILURE);
	while (lst != NULL)
	{
		if (ft_strcmp(lst->name, to_find) == 0)
		{
			if (last_char(name) == SUCCESS)
			{
				free(lst->value);
				lst->value = ft_strdup(value);
			}
			else
			{
				temp = lst->value;
				lst->value = ft_strjoin(lst->value, value);
				free(temp);
			}
			break ;
		}
		lst = lst->next;
	}
	change_equal_to_one(lst, name);
	return (SUCCESS);
}

t_env	*add_back_with_equal(t_env *lst, char *name, char *value)
{
	char	*tmp;

	tmp = NULL;
	if (last_char(name) == PLUS)
	{
		tmp = ft_strndup(tmp, name, (ft_strlen(name) - 1));
		ft_lstadd_back_env(&lst, ft_lstnew_env(tmp, value));
		change_equal_to_one(lst, tmp);
		free(name);
	}
	else if (last_char(name) == SUCCESS)
	{
		ft_lstadd_back_env(&lst, ft_lstnew_env(name, value));
		change_equal_to_one(lst, name);
	}
	return (lst);
}
