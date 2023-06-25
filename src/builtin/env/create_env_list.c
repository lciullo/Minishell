/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:38:34 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/25 16:38:35 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*fill_list_env(char *row, t_env *lst);
static t_env	*if_empty_env(t_env *lst);
static t_env	*begin_empty_lst(t_env *lst);

t_env	*creat_env(char **env)
{
	size_t		row;
	t_env		*lst;

	lst = NULL;
	row = 0;
	if (env[0] == NULL)
	{
		lst = if_empty_env(lst);
		return (lst);
	}
	else
	{
		while (env[row] != NULL)
		{
			lst = fill_list_env(env[row], lst);
			if (!lst)
				return (NULL);
			row++;
		}
	}
	return (lst);
}

static t_env	*if_empty_env(t_env *lst)
{
	lst = begin_empty_lst(lst);
	if (!lst)
		return (NULL);
	ft_lstadd_back_env(&lst, ft_lstnew_env(ft_strdup("_"), \
			ft_strdup("/usr/bin/env"), 1));
	if (!lst)
	{
		ft_lstclear_env(&lst, free);
		return (NULL);
	}
	ft_lstadd_back_env(&lst, ft_lstnew_env(ft_strdup("OLDPWD"), NULL, 0));
	if (!lst)
	{
		ft_lstclear_env(&lst, free);
		return (NULL);
	}
	return (lst);
}

static t_env	*begin_empty_lst(t_env *lst)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(NULL, 0);
	ft_lstadd_back_env(&lst, ft_lstnew_env(ft_strdup("PWD"), pwd, 1));
	if (!lst)
	{
		ft_lstclear_env(&lst, free);
		return (NULL);
	}
	ft_lstadd_back_env(&lst, ft_lstnew_env(ft_strdup("SHLVL"), \
			ft_strdup("1"), 1));
	if (!lst)
	{
		ft_lstclear_env(&lst, free);
		return (NULL);
	}
	return (lst);
}

static t_env	*fill_list_env(char *row, t_env *lst)
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
	ft_lstadd_back_env(&lst, ft_lstnew_env(name, value, 1));
	if (!lst)
	{
		ft_lstclear_env(&lst, free);
		return (NULL);
	}
	return (lst);
}

size_t	begin_of_name(char *path)
{
	size_t	len;

	len = 0;
	while (path[len] != '=' && path[len] != '\0')
		len++;
	return (len);
}
