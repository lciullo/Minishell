/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:52:30 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/16 11:02:54 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid(int c)
{
	if ((c >= '0' && c <= '9') || (c == ' '))
	{
		return (SUCCESS);
	}
	else
		return (FAILURE);
}

static int	ft_is_numeric(char *nb)
{
	int	i;

	i = 0;
	while (nb[i] != '\0')
	{
		if (is_valid(nb[i]) == FAILURE)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	implement_exit(char **cmd, t_exec *data)
{
	int	nb;

	if (ft_strcmp(cmd[0], "exit") == 0 && !cmd[1])
	{
		data->end = 1;
		return (0);
	}
	else if (cmd[2])
	{
		data->end = 0;
		ft_dprintf(2, "exit\nminishell: exit: too many arguments\n");
		return (1);
	}
	if ((ft_atoi_exit(cmd[1], &nb) == FAILURE) || ft_is_numeric(cmd[1]) == FAILURE)
	{
		ft_dprintf(2, "exit\nminishell: exit: %s: numeric argument is required\n",
			cmd[1]);
		data->end = 1;
		return (FAILURE);
	}
	data->end = 1;
	return (SUCCESS);
}
