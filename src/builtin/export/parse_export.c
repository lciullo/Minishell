/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:39:08 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/06 15:43:01 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	first_char(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_'))
		return (SUCCESS);
	else
	{
		ft_dprintf(2, "export: not a valid identifier\n");
		return (FAILURE);
	}
}

int	last_char(char *name)
{
	size_t	end;
	char	c;

	if (ft_strlen(name) > 1)
		end = ft_strlen(name) - 1;
	else
		end = 1;
	c = name[end - 1];
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '+') || \
		(c >= '0' && c <= '9'))
	{
		if (c == '+')
			return (PLUS);
		else
			return (SUCCESS);
	}
	return (FAILURE);
}

static int	is_valid(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') \
	|| (c >= 'A' && c <= 'Z') || (c == '_') || (c == '='))
		return (SUCCESS);
	else
		return (FAILURE);
}

static	int	is_valid_syntax(char *name)
{
	size_t	i;
	size_t	end;

	i = 1;
	if (ft_strlen(name) > 1)
		end = ft_strlen(name) - 1;
	else
		end = 1;
	while (name[i] != '\0' && i < end)
	{
		if (is_valid(name[i]) == FAILURE)
		{
			ft_dprintf(2, "export: not a valid identifier\n");
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int	parse_name(char *name)
{
	if (is_valid_syntax(name) == FAILURE)
		return (FAILURE);
	if (first_char(name[0]) == FAILURE)
		return (FAILURE);
	if (last_char(name) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
