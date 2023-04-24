/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:37:22 by lciullo           #+#    #+#             */
/*   Updated: 2023/04/24 14:49:58 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	count_dash(char *echo)
{
	int	i;
	int	dash;

	i = 0;
	dash = 0;
	while (echo && echo[i])
	{
		if (echo[i] == '-')
			dash++;
		i++;
	}
	return (dash);
}

static	int	is_valid_option(char *echo)
{
	size_t	i;

	i = 0;
	while (echo && echo[i] != 0 && (echo[i] == '-' || echo[i] == 'n'))
		i++;
	if (ft_strlen(echo) == i)
		return (0);
	return (1);
}

static	int	parse_option(char *echo)
{
	int		dash;

	dash = count_dash(echo);
	if (dash != 1)
		return (1);
	if (is_valid_option(echo) == 1)
		return (1);
	return (0);
}

int	implement_echo(char **echo)
{
	int	i;
	int	option;

	i = 1;
	option = 0;
	if (!echo)
	{
		ft_dprintf(1, "\n");
		return (0);
	}
	if (echo[1])
		option = parse_option(echo[1]);
	while (echo && echo[i] != NULL && parse_option(echo[i]) == 0)
		i++;
	while (echo && echo[i] != NULL)
	{
		ft_dprintf(1, "%s", echo[i]);
		if (echo[i + 1])
			ft_dprintf(1, " ");
		i++;
	}
	if (option)
		ft_dprintf(1, "\n");
	return (0);
}
