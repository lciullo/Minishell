/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:59:48 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/14 12:48:26 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	nb_arguments(char **cmd)
{
	size_t	i;

	i = 0;
	if (!cmd)
		return (FAILURE);
	while (cmd[i] != NULL)
		i++;
	return (i);
}

int	implement_cd(char **cmd, t_env **lst)
{
	(void)lst;
	if (cmd[1])
	{
		if (cmd[1][0] == '-')
		{
			ft_dprintf(2, "Invalid option, subject : cd with no options\n");
			return (FAILURE);
		}
	}
	if (nb_arguments(cmd) > 2)
	{
		ft_dprintf(2, "minishell: cd: too many arguments\n");
		return (FAILURE);
	}
	if (chdir(cmd[1]) == FAILURE)
	{
		ft_dprintf(2, "minishell: cd: path not fou\n");
		return (FAILURE);
	}
	ft_dprintf(2, "In cd\n");
	return (SUCCESS);
}
