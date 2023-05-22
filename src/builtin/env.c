/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:12:43 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/18 17:33:44 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	begin_of_name(char *path)
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
	char		*name;
	char		*value;

	name = NULL;
	value = NULL;
	start = begin_of_name(row);
	if (!start)
		return (NULL);
	name = ft_strndup(name, row, start);
	if (!name)
		return (NULL);
	value = ft_strndup(value, &row[start + 1], ft_strlen(row));
	if (!value)
		return (free(name), NULL);
	ft_lstadd_back_env(&lst_env, ft_lstnew_env(name, value));
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
