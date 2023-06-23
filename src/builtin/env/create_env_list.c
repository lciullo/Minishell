#include "minishell.h"

static t_env	*fill_list_env(char *row, t_env *lst);
static t_env	*if_empty_env(t_env *lst);
//static t_env	*get_shlvl_list(t_env *lst);

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
	//lst = get_shlvl_list(lst);
	return (lst);
}

static t_env	*if_empty_env(t_env *lst)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(NULL, 0);
	ft_lstadd_back_env(&lst, ft_lstnew_env(ft_strdup("PWD"), pwd, 1));
	ft_lstadd_back_env(&lst, ft_lstnew_env(ft_strdup("SHLVL"), ft_strdup("1"), 1));
	ft_lstadd_back_env(&lst, ft_lstnew_env(ft_strdup("_"), ft_strdup("/usr/bin/env"), 1));
	ft_lstadd_back_env(&lst, ft_lstnew_env(ft_strdup("OLDPWD"), NULL, 0));
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
	return (lst);
}

/*static t_env	*get_shlvl_list(t_env *lst)
{
	t_env 	*copy;
	int		nb;

	copy = lst;
	nb = 0;
	if (!lst)
		return (NULL);
	while (copy != NULL && ft_strcmp(copy->name, "SHLVL") != 0)
		copy = copy->next;
	if (!copy)
		return (NULL);
	if (copy->value)
	{
		nb = ft_atoi(copy->value);
		if (nb >= 1000)
		{
			ft_putstr_fd("shell level 1000 too high, resetting to 1", 2);
			nb = 1;
		}
		else
			nb++;
		free(copy->value);
		copy->value = ft_itoa(nb);
		if (!copy->value)
			return (NULL);
	}
	return (lst);
}*/

size_t	begin_of_name(char *path)
{
	size_t	len;

	len = 0;
	while (path[len] != '=' && path[len] != '\0')
		len++;
	return (len);
}
