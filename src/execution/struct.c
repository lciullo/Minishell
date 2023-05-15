/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 09:29:59 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/15 15:24:23 by lciullo          ###   ########.fr       */
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
	data->i = 1;
	data->infile = 0;
	data->outfile = 1;
	data->expand = 0;
	data->nb_cmds = get_nb_commands(list);
	data->fd[0] = 0;
	data->fd[1] = 1;
	data->prev_fd = 0;
	data->infile_opened = 0;
	data->outfile_opened = 1;
	data->cmd_with_path = NULL;
	data->cmd = NULL;
	data->paths = NULL;
	data->env_path = NULL;
}
