/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:52:30 by lciullo           #+#    #+#             */
/*   Updated: 2023/04/24 17:05:25 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	implement_exit(char **exit)
{
	int	nb;

	nb = ft_atoi(exit[1]);
	(void)nb;
	//ft_dprintf(2, "in exit %d\n", nb);
	return (0);
}
