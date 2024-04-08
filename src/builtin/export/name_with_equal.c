/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_with_equal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:18:35 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/25 16:18:37 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_value(t_env *lst, char *value, t_export *stat);
static int	do_plus_equal_case(t_env *lst, char *value);

int	search_and_replace_value(t_env *lst, char *name, \
		char *value, t_export *stat)
{
	while (lst != NULL)
	{
		if (ft_strcmp(lst->name, name) == 0)
		{
			if (add_value(lst, value, stat) == FAILURE)
				return (FAILURE);
			break ;
		}
		lst = lst->next;
	}
	change_equal_to_one(&lst, name);
	return (SUCCESS);
}

static int	add_value(t_env *lst, char *value, t_export *stat)
{
	if (stat->plus == FALSE)
	{
		free(lst->value);
		lst->value = ft_strdup(value);
		if (!lst->value)
			return (FAILURE);
	}
	else
	{
		if (do_plus_equal_case(lst, value) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

static int	do_plus_equal_case(t_env *lst, char *value)
{
	char	*tmp;

	tmp = NULL;
	if (lst->value)
	{
		tmp = lst->value;
		lst->value = ft_strjoin(lst->value, value);
		free(tmp);
		if (!lst->value)
			return (FAILURE);
	}
	else
	{
		lst->value = ft_strdup(value);
		if (!lst->value)
			return (FAILURE);
	}
	return (SUCCESS);
}

t_env	*add_back_with_equal(t_env **lst, char *name, char *value)
{
	ft_lstadd_back_env(lst, ft_lstnew_env(name, value, 1));
	if (!lst)
	{
		ft_lstclear_env(lst, free);
		return (NULL);
	}
	return (*lst);
}
