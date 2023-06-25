/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_executable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 15:43:39 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/25 15:43:40 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_executable(char *cmd, t_exec *data, t_list *list, t_env **lst)
{
	struct stat	info;
	char		*str;

	str = NULL;
	if (stat(cmd, &info) == 0)
	{
		if (!(info.st_mode & S_IXUSR))
		{
			g_exit_status = 126;
			write(2, "Permission denied\n", 19);
			return (FAILURE);
		}
		if (S_ISDIR(info.st_mode))
		{
			g_exit_status = 126;
			write(2, "is a directory\n", 16);
			return (FAILURE);
		}
		return (SUCCESS);
	}
	write(2, "No such file or directory\n", 27);
	g_exit_status = 127;
	clear_is_executable(data, list, lst);
	return (FAILURE);
}
