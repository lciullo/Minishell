/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 09:29:59 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/31 15:42:33 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	get_nb_builtin(t_list *list)
{
	int	nb_builtin;

	nb_builtin = 0;
	while (list != NULL)
	{
		if (list->type == BUILTIN)
			nb_builtin++;
		list = list->next;
	}
	return (nb_builtin);
}

void	free_struct(t_exec *data)
{
	free_array(data->env_path);
	free(data->cmd_with_path);
	free(data->pids);
	free(data->fd_heredoc);
}

int	init_struct(t_list *list, t_exec *data, t_data *parsing)
{
	data->exec_progress = 0;
	data->nb_pids = 0;
	data->infile = 0;
	data->outfile = 1;
	data->expand = 0;
	data->old_fd[0] = 0;
	data->old_fd[1] = 0;
	data->new_fd[0] = 0;
	data->new_fd[1] = 0;
	data->in_dir = 0;
	data->out_dir = 0;
	data->nb_cmds = parsing->nbr_pipe + 1;
	data->nb_builtin = get_nb_builtin(list);
	data->nb_heredoc = parsing->nbr_here_doc;
	data->pids = ft_calloc(data->nb_cmds, sizeof(pid_t));
	if (!data->pids)
		return (-1);
	data->fd_heredoc = ft_calloc(data->nb_heredoc, sizeof(int));
	if (!data->fd_heredoc)
	{
		free(data->pids);
		return (-1);
	}
	data->prev_fd = 0;
	data->cmd_with_path = NULL;
	data->cmd = NULL;
	data->paths = NULL;
	data->env_path = NULL;
	return (0);
}
