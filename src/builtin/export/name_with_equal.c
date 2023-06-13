/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_with_equal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisa <lisa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:08:52 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/13 12:25:05 by lisa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_and_replace_value(t_env *lst, char *name, char *value, t_export *stat)
{
	char	*temp;

	temp = NULL;
	while (lst != NULL)
	{
		if (ft_strcmp(lst->name, name) == 0)
		{
			if (stat->plus == FALSE)
			{
				free(lst->value);
				lst->value = ft_strdup(value);
			}
			else
			{
				if (lst->value)
				{
					temp = lst->value;
					lst->value = ft_strjoin(lst->value, value);
					free(temp);
				}
				else
					lst->value = ft_strdup(value);
			}
			break ;
		}
		lst = lst->next;
	}
	change_equal_to_one(&lst, name);
	return (SUCCESS);
}

t_env	*add_back_with_equal(t_env **lst, char *name, char *value)
{
	ft_lstadd_back_env(lst, ft_lstnew_env(name, value, 1));
	//change_equal_to_one(lst, name);
	return (*lst);
}
