/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:12:43 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/02 13:13:45 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	begin_of_variable(char *path)
{
	size_t	len;

	len = 0;
	while (path[len] != '=')
		len++;
	return (len);
}

static t_lst_env	*fill_list_env(char *row, t_lst_env *lst_env)
{
	size_t		start;
	char		*variable;
	char		*value;

	variable = NULL;
	value = NULL;
	start = begin_of_variable(row);
	if (!start)
		return (NULL);
	variable = ft_strndup(variable, row, start);
	if (!variable)
		return (NULL);
	value = ft_strndup(value, &row[start + 1], ft_strlen(row));
	if (!value)
		return (free(variable), NULL);
	ft_lstadd_back_env(&lst_env, ft_lstnew_env(variable, value));
	return (lst_env);
}

int	implement_env(char **env)
{
	size_t		row;
	t_lst_env	*lst_env;

	lst_env = NULL;
	row = 0;
	while (env[row] != NULL)
	{
		lst_env = fill_list_env(env[row], lst_env);
		row++;
	}
	list_print_env(lst_env);
	return (1);
}
