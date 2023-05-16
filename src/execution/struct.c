/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 09:29:59 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/16 15:07:28 by lciullo          ###   ########.fr       */
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

static void	allocated_pids_array(t_exec *data)
{
	data->pids = ft_calloc(data->nb_cmds, sizeof(pid_t));
}

void	init_struct(t_list *list, t_exec *data)
{
	data->i = 0;
	data->index = 0;
	data->infile = 0;
	data->outfile = 1;
	data->expand = 0;
	data->old_fd[0] = 0;
	data->old_fd[1] = 0;
	data->new_fd[0] = 0;
	data->new_fd[1] = 0;
	data->nb_cmds = get_nb_commands(list);
	allocated_pids_array(data);
	data->prev_fd = 0;
	data->cmd_with_path = NULL;
	data->cmd = NULL;
	data->paths = NULL;
	data->env_path = NULL;
}
