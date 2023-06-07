/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:52:54 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/07 17:46:55 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*on ne regarde que token de 1*/

#include "minishell.h"



static	char	*remove_plus_in_name(char *name)
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

//si ya des leaks tmp 
//fixe le += plus tard name-1 boucler sur les arguments



int	search_and_replace_value(t_env *lst, char *name, char *value)
{
	char	*to_find;

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
				lst->value = ft_strjoin(lst->value, value);
			}
			break ;
		}
		lst = lst->next;
	}
	return (SUCCESS);
}

int	add_to_export(t_env **lst, char *name, char *value)
{
	(void)value;
	if (is_in_env(*lst, name) == SUCCESS)
		search_and_replace_value(*lst, name, value);
	return (SUCCESS);
}


int	implement_export(char **token, t_exec *data, t_env **lst)
{
	char	*name;
	char	*value;
	int		i;


	name = NULL;
	value = NULL;
	i = 0;
	(void)data;
	if (!token[1])
		print_export(*lst);
	else if (token[1][0] == '-')
	{
		ft_dprintf(2, "Invalid option, subject : export with no options\n");
		return (FAILURE);
	}
	else if (token[1][0] != '-')
	{
		while (token[i])
		{
			name = get_name_variable(token[i]);
			if (parse_name(name) == FAILURE)
				return (FAILURE);
			if (is_equal(token[i]) == EQUAL)
				value = get_value_variable(token[i]);
			add_to_export(lst, name, value);
			free(name);
			if (is_equal(token[i]) == EQUAL)
				free(value);
			i++;
		}
	}
	return (SUCCESS);
}
