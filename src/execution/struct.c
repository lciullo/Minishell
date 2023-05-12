/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 09:29:59 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/11 16:50:34 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	get_nb_commands(t_list *list)
{
	int	nb_cmds;

	nb_cmds = 0;
	while (list != NULL)
	{
		if (list->type == TOKEN || list->type == BUILTIN)
			nb_cmds++;
		list = list->next;
	}
	return (nb_cmds);
}

void	init_struct(t_list *list, t_exec *data)
{
	data->infile = 0;
	data->outfile = 0;
	data->expand = 0;
	data->nb_cmds = get_nb_commands(list);
	data->cmd_with_path = NULL;
	data->cmd = NULL;
	data->paths = NULL;
	data->env_path = NULL;
}
