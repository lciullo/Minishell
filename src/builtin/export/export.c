#include "minishell.h"

static int	loop_for_export_arguments(char **token, t_env **lst);

int	implement_export(char **token, t_env **lst)
{
	if (!token[1])
		print_export(*lst);
	if (loop_for_export_arguments(token, lst) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
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

int	add_to_export(t_env **lst, char *name, char *value, t_export *stat)
{

	if (stat->equal == TRUE)
	{
		if (stat->in_env == TRUE)
			search_and_replace_value(*lst, name, value, stat);
		else
			*lst = add_back_with_equal(lst, name, value);
	}
	else
	{
		if (stat->in_env == FALSE)
		{
			ft_lstadd_back_env(lst, ft_lstnew_env(name, value, 0));
		}
	}
	return (SUCCESS);
}

int	check_only_equal(char *token)
{
	if (token[0] == '=')
	{
		ft_dprintf(2, "export %s : not a valid identifier\n", token);
		g_exit_status = 1;
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	loop_for_export_arguments(char **token, t_env **lst)
{
	t_export	stat;
	int			i;

	stat.equal = 0;
	stat.in_env = 0;
	stat.plus = 0;
	i = 1;
	while (token[i])
	{
		if (token[i][0] == '-')
		{
			ft_dprintf(2, "Invalid option, subject : export with no options\n");
			g_exit_status = 2;
		}
		else
			check_name_by_name(token[i], lst, &stat);
		i++;
	}
	return (SUCCESS);
}



