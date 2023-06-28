/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:19:07 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/25 19:19:13 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_numeric(char *nb);
static int	is_valid(int c);

void	implement_exit(char **cmd, t_exec *data)
{
	int	nb;

	if (ft_strcmp(cmd[0], "exit") == 0 && !cmd[1])
	{
		data->end = 1;
		return ;
	}
	if (((ft_atoi_exit(cmd[1], &nb) == -1) || ft_is_numeric(cmd[1]) == -1))
	{
		g_exit_status = 2;
		ft_putstr_fd("minishell: numeric argument is required\n", 2);
		data->end = 1;
		return ;
	}
	if (cmd[2])
	{
		data->end = 0;
		g_exit_status = 1;
		ft_putstr_fd("exit\nminishell: too many arguments\n", 2);
		return ;
	}
	data->end = 1;
	g_exit_status = nb;
	return ;
}

static int	is_valid(int c)
{
	if ((c >= '0' && c <= '9') || (c == ' ') || (c == '-' || c == '+'))
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
