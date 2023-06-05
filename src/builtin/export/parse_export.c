/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:39:08 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/05 16:39:07 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	first_char(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_'))
		return (0);
	else
	{
		ft_dprintf(2, "export: not a valid identifier\n");
		return (-1);
	}
}

static int	last_char(char *name)
{
	int		last;
	char	c;

	if (ft_strlen(name) > 1)
		last = ft_strlen(name) - 1;
	else
		last = 1;
	c = name[last - 1];
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '+') || \
		(c >= '0' && c <= '9'))
	{
		if (c == '+')
			return (PLUS);
		else
			return (SUCCESS);
	}
	return (FAILLURE);
}

static int	parse_name(char *name)
{
	if (first_char(name[0]) == -1)
		return (-1);
	if (last_char(name) == -1)
		return (-1);
	return (0);
}

int	manage_export(char **token, t_exec *data, t_env *lst)
{
	int	row;

	row = 0;
	(void)data;
	(void)lst;
	if (token[1])
	{
		if (parse_name(token[1]) == -1)
			return (-1);
	}
	return (0);
}
