/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:19:15 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/25 20:31:35 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_current_directory_path(void);

int	implement_pwd(char **cmd)
{
	if (cmd[1])
	{
		if (cmd[1][0] == '-')
		{
			ft_putstr_fd("Invalid option, subject : pwd with no options\n", 2);
			g_exit_status = 2;
			return (FAILURE);
		}
	}
	return (check_current_directory_path());
}

static int	check_current_directory_path(void)
{
	char	*current_directory_path;

	current_directory_path = NULL;
	current_directory_path = getcwd(NULL, 0);
	if (current_directory_path == NULL)
	{
		ft_putstr_fd("pwd: error retrieving current directory\n", 2);
		g_exit_status = 0;
		free(current_directory_path);
		return (errno);
	}
	if (current_directory_path)
	{
		ft_dprintf(1, "%s\n", current_directory_path);
		free(current_directory_path);
	}
	g_exit_status = 0;
	return (0);
}
