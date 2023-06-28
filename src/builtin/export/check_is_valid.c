/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_is_valid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:17:51 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/25 19:34:32 by cllovio          ###   ########.fr       */
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

int	is_valid_export(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') \
	|| (c >= 'A' && c <= 'Z') || (c == '_') || (c == '='))
		return (SUCCESS);
	else
		return (FAILURE);
}

int	is_valid_syntax(char *name)
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
		if (is_valid_export(name[i]) == FAILURE)
		{
			ft_putstr_fd("export : not a valid identifier\n", 2);
			g_exit_status = 1;
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}
