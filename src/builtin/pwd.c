/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:35:56 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/16 09:10:01 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	implement_pwd(char **cmd)
{
	char	*current_directory_path;

	current_directory_path = NULL;
	if (cmd[1])
	{
		if (cmd[1][0] == '-')
		{
			ft_dprintf(2, "Invalid option, subject : pwd with no options\n");
			return (FAILURE);
		}
	}
	current_directory_path = getcwd(NULL, 0);
	if (current_directory_path[0] == '\0')
	{
		ft_dprintf(2, "doublechoc-> : %s\n", strerror(errno));
		return (errno);
	}
	if (current_directory_path)
	{
		ft_dprintf(1, "%s\n", current_directory_path);
		free(current_directory_path);
	}
	return (0);
}
