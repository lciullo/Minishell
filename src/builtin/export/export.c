/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:18:16 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/25 23:57:07 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	loop_for_export_arguments(char **token, t_env **lst, t_exec *data);

void	implement_export(char **token, t_env **lst, t_exec *data)
{
	if (!token[1])
		print_export(*lst);
	if (loop_for_export_arguments(token, lst, data) == FAILURE)
		return ;
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
			if (!lst)
			{
				ft_lstclear_env(lst, free);
				return (FAILURE);
			}
		}
	}
	return (SUCCESS);
}

int	check_only_equal(char *token)
{
	if (token[0] == '=')
	{
		ft_putstr_fd("export : not a valid identifier\n", 2);
		g_exit_status = 1;
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	loop_for_export_arguments(char **token, t_env **lst, t_exec *data)
{
	t_export	stat;
	int			i;

	stat.equal = 0;
	stat.in_env = 0;
	stat.plus = 0;
	i = 1;
	g_exit_status = 0;
	while (token[i])
	{
		if (token[i][0] == '-')
		{
			ft_putstr_fd("subject : export with no options\n", 2);
			g_exit_status = 2;
		}
		else
		{	
			if (check_name_by_name(token[i], lst, &stat) == FAILURE)
				data->check_export = g_exit_status;
		}
		i++;
	}
	if (data->check_export != 0)
		g_exit_status = data->check_export;
	return (SUCCESS);
}
