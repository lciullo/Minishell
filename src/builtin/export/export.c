/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:52:54 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/10 19:17:21 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*on ne regarde que token de 1*/
//si ya des leaks tmp 
//fixe le += plus tard name-1 boucler sur les arguments
/*void	print_print(t_env *lst)
{
	t_env	*copy;

	copy = lst;
	while (copy)
	{
		ft_dprintf(1, "[%s] =  [%s]\n", copy->name, copy->value);
		ft_dprintf(1, "%d\n", copy->equal);
		copy = copy->next;
	}
}*/

#include "minishell.h"

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
			*lst = add_back_with_equal(*lst, name, value);
	}
	else
	{
		if (stat->in_env == FALSE)
		{
			ft_lstadd_back_env(lst, ft_lstnew_env(name, value));
			change_equal_to_zero(*lst, name);
		}
	}
	return (SUCCESS);
}

static int	check_name_by_name(char *token, t_env **lst, t_export *stat)
{
	char		*name;
	char		*value;

	name = NULL;
	value = NULL;
	if (token[0] == '=' && token[1] == '\0')
	{
		ft_dprintf(2, "export %s : not a valid identifier\n", token);
		return (FAILURE);
	}
	name = get_name_variable(token, stat);
	if (!name)
		return (FAILURE);
	if (parse_name(token) == FAILURE)
	{
		free(name);
		return (FAILURE);
	}
	if (is_in_env(*lst, name) == SUCCESS)
		stat->in_env = TRUE;
	if (stat->equal == TRUE)
		value = get_value_variable(token);
	add_to_export(lst, name, value, stat);
	if (stat->in_env == TRUE && stat->equal == FALSE && stat->plus == FALSE)
		free(name);
	else if (stat->in_env == TRUE && stat->equal == TRUE && stat->plus == FALSE)
	{
		free(name);
		free(value);
	}
	else if (stat->in_env == TRUE && stat->equal == TRUE && stat->plus == TRUE)
	{
		free(name);
		free(value);
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
		check_name_by_name(token[i], lst, &stat);
		i++;
	}
	return (SUCCESS);
}

int	implement_export(char **token, t_env **lst)
{
	if (!token[1])
		print_export(*lst);
	else if (token[1][0] == '-')
	{
		ft_dprintf(2, "Invalid option, subject : export with no options\n");
		return (FAILURE);
	}
	else if (token[1][0] != '-')
	{
		if (loop_for_export_arguments(token, lst) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
