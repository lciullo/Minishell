/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:52:30 by lciullo           #+#    #+#             */
/*   Updated: 2023/04/26 16:05:15 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	implement_exit(char **cmd, t_exec *data)
{
	long	nb;

	nb = 0;
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
	nb = ft_atoi_long(cmd[1]);
	if (nb == -1)
	{
		ft_dprintf(2, "exit\nminishell: exit: %s: numeric argument is required\n",
			cmd[1]);
		return (2);
	}
	data->end = 1;
	nb = (nb + 256) % 256;
	return (nb);
}
