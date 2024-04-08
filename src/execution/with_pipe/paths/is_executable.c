/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_executable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 15:43:39 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/25 19:31:14 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_executable(char *cmd, t_exec *data, t_list *list, t_env **lst)
{
	struct stat	info;

	if (stat(cmd, &info) == 0)
	{
		if (!(info.st_mode & S_IXUSR))
		{
			g_exit_status = 126;
			ft_putstr_fd("Permission denied\n", 2);
			return (FAILURE);
		}
		if (S_ISDIR(info.st_mode))
		{
			g_exit_status = 126;
			ft_putstr_fd("is a directory\n", 2);
			return (FAILURE);
		}
		return (SUCCESS);
	}
	ft_putstr_fd("No such file or directory\n", 2);
	g_exit_status = 127;
	clear_is_executable(data, list, lst);
	return (FAILURE);
}
