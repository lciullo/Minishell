/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisa <lisa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:35:56 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/13 18:00:59 by lisa             ###   ########.fr       */
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
	if (!current_directory_path)
	{
		ft_dprintf(2, "doublechoc-> : %s\n", strerror(errno));
		return (errno);
	}
	ft_dprintf(1, "%s\n", current_directory_path);
	free(current_directory_path);
	return (0);
}
