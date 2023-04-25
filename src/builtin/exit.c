/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisa <lisa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:52:30 by lciullo           #+#    #+#             */
/*   Updated: 2023/04/25 11:31:50 by lisa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	implement_exit(char **exit, t_exec *data)
{
	long	nb;

	nb = 0;
	if(ft_strcmp(exit[0], "exit") == 0 && !exit[1])
	{
		data->end = 1;
		return (0);
	}
	else if (exit[2])
	{
		data->end = 0;
		ft_dprintf(2, "exit : to many arguments\n");
		return (1);
	}
	nb = ft_atoi_long(exit[1]);
	if (nb == -1)
	{
		ft_dprintf(2, "exit : %s numeric argument is required\n", exit[1]);
		return (2);
	}
	data->end = 1;
	nb = (nb + 256) % 256;
	return (nb);
}
