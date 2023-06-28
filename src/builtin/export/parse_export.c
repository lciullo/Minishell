/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:18:43 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/25 19:30:01 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_value(char *value)
{
	size_t	i;

	i = 0;
	while (value[i] != '\0')
	{
		if (value[i] == '(' || value[i] == ')')
		{
			ft_putstr_fd("minishell : syntax error near unexpected token \n", 2);
			g_exit_status = 2;
			return (FAILURE);
		}
		if (value[i] == '&' || value[i] == ';')
		{
			ft_putstr_fd("export : not a valid identifier\n", 2);
			g_exit_status = 1;
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int	parse_name(char *name)
{
	char	*tmp;
	size_t	start;

	tmp = NULL;
	start = begin_of_name(name);
	tmp = ft_strndup(tmp, name, start);
	if (!tmp)
		return (FAILURE);
	if (is_valid_syntax(tmp) == FAILURE)
		return (free(tmp), FAILURE);
	if (first_char(tmp[0]) == FAILURE)
	{
		ft_putstr_fd("export : not a valid identifier\n", 2);
		g_exit_status = 1;
		return (free(tmp), FAILURE);
	}
	if (last_char(tmp) == FAILURE)
	{
		ft_putstr_fd("export : not a valid identifier\n", 2);
		g_exit_status = 1;
		return (free(tmp), FAILURE);
	}
	return (free(tmp), SUCCESS);
}
