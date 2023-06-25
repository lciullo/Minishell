/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:38:40 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/25 19:38:20 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	implement_env(char **cmd, t_env *lst)
{
	g_exit_status = 0;
	if (cmd[1])
	{
		ft_putstr_fd("subject : env with no options or arguments\n", 2);
		g_exit_status = 127;
		return ;
	}
	if (!lst)
		return ;
	list_print_env(lst);
	return ;
}
