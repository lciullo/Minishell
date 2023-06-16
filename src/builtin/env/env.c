/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:12:43 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/15 17:28:35 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	begin_of_name(char *path)
{
	size_t	len;

	len = 0;
	while (path[len] != '=' && path[len] != '\0')
		len++;
	return (len);
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
	return (lst);
}

t_env	*creat_env(char **env)
{
	size_t		row;
	t_env		*lst;
	char		*pwd;

	lst = NULL;
	row = 0;
	pwd = NULL;
	if (env[0] == NULL)
	{
		pwd = getcwd(NULL, 0);
		ft_lstadd_back_env(&lst, ft_lstnew_env(ft_strdup("PWD"), pwd, 1));
		ft_lstadd_back_env(&lst, ft_lstnew_env(ft_strdup("SHLVL"), ft_strdup("1"), 1));
		ft_lstadd_back_env(&lst, ft_lstnew_env(ft_strdup("_"), ft_strdup("/usr/bin/env"), 1));
		ft_lstadd_back_env(&lst, ft_lstnew_env(ft_strdup("OLDPWD"), NULL, 0));
		return (lst);
	}
	while (env[row] != NULL)
	{
		lst = fill_list_env(env[row], lst);
		row++;
	}
	return (lst);
}

int	implement_env(char **cmd, t_env *lst)
{
	if (cmd[1])
	{
		ft_dprintf(2, "subject : env with no options or arguments\n");
		return (FAILURE);
	}
	if (!lst)
		return (FAILURE);
	list_print_env(lst);
	return (1);
}
