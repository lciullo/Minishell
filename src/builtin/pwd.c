/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:35:56 by lciullo           #+#    #+#             */
/*   Updated: 2023/04/26 16:03:09 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	implement_pwd(char **cmd)
{
	char	*current_directory_path;

	(void)cmd;
	current_directory_path = NULL;
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
