/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:59:26 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/06 16:26:06 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_equal(char *name)
{
	size_t	i;

	i = 0;
	while (name[i] != '\0')
	{
		if (name[i] == '=')
			return (EQUAL);
		i++;
	}
	return (NO_EQUAL);
}

char	*get_name_variable(char *row)
{
	char		*name;
	size_t		start;

	name = NULL;
	start = begin_of_name(row);
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
	ft_dprintf(1, "start %d\n", start);
	value = ft_strndup(value, &row[start + 1], ft_strlen(row));
	if (!value)
		return (NULL);
	return (value);
}
