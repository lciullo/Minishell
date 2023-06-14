/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisa <lisa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:59:48 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/13 15:37:59 by lisa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t nb_arguments(char **cmd)
{
	size_t	i;

	i = 0;
	if (!cmd)
		return (FAILURE);
	while (cmd[i] != NULL)
		i++;
	return (i);
}

int	implement_cd(char **cmd)
{
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
	ft_dprintf(2, "In cd\n");
	return (SUCCESS);
}
