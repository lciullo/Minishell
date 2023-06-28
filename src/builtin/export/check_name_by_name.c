/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_name_by_name.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:17:59 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/25 16:18:01 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_name_by_name(char *token, t_env **lst, t_export *stat)
{
	char		*name;
	char		*value;

	name = NULL;
	value = NULL;
	if (check_only_equal(token) == FAILURE)
		return (FAILURE);
	name = get_name_variable(token, stat);
	if (!name)
		return (FAILURE);
	if (parse_name(token) == FAILURE)
		return (free(name), FAILURE);
	if (is_in_env(*lst, name) == SUCCESS)
		stat->in_env = TRUE;
	if (stat->equal == TRUE)
	{
		value = get_value_variable(token);
		if (parse_value(value) == FAILURE)
			return (free(name), free(value), FAILURE);
	}
	add_to_export(lst, name, value, stat);
	clear_export_end_according_cases(stat, name, value);
	g_exit_status = 0;
	return (SUCCESS);
}

char	*get_name_variable(char *row, t_export *stat)
{
	char		*name;
	int			start;

	name = NULL;
	start = len_of_name(row, stat);
	if (start == FAILURE)
		return (NULL);
	name = ft_strndup(name, row, start);
	if (!name)
		return (NULL);
	return (name);
}

char	*get_value_variable(char *row)
{
	size_t		start;
	char		*value;

	value = NULL;
	start = begin_of_name(row);
	value = ft_strndup(value, &row[start + 1], ft_strlen(row));
	if (!value)
		return (NULL);
	return (value);
}
