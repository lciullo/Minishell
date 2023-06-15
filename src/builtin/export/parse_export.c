/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:39:08 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/15 14:29:38 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	first_char(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_'))
		return (SUCCESS);
	else
		return (FAILURE);
}

int	last_char(char *name)
{
	size_t	end;
	char	c;

	end = 0;
	if (ft_strlen(name) > 1)
		end = ft_strlen(name) - 1;
	else
		end = 0;
	c = name[end];
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '+') || \
		(c >= '0' && c <= '9') || (c == '_'))
		return (SUCCESS);
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
			ft_dprintf(2, "export '%s' : not a valid identifier\n", name);
			g_exit_status = 1;
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}


int	parse_value(char *value)
{
	size_t	i;

	i = 0;
	while (value[i] != '\0')
	{
		if (value[i] == '(' || value[i] == ')')
		{
			ft_dprintf(2, "minishell : syntax error near unexpected token \'%c\'\n", value[i]);
			g_exit_status = 2;
			return (FAILURE);
		} 
		if (value[i] == '&' || value[i] == ';' || value[i] == '!')
		{
			ft_dprintf(2, "export %c : not a valid identifier\n", value[i]);
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
	{
		free(tmp);
		return (FAILURE);
	}
	if (first_char(tmp[0]) == FAILURE)
	{
		ft_dprintf(2, "export '%s': not a valid identifier\n", name);
		g_exit_status = 1;
		free(tmp);
		return (FAILURE);
	}
	if (last_char(tmp) == FAILURE)
	{
		ft_dprintf(2, "export '%s': not a valid identifier\n", name);
		g_exit_status = 1;
		free(tmp);
		return (FAILURE);
	}
	free(tmp);
	return (SUCCESS);
}
