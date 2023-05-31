/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 09:29:59 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/30 16:01:10 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	get_nb_commands(t_list *list)
{
	int	nb_cmds;

	nb_cmds = 1;
	while (list != NULL)
	{
		if (list->type == PIPE)
			nb_cmds++;
		list = list->next;
	}
	return (nb_cmds);
}

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

static	int	get_nb_heredoc(t_list *list)
{
	int	nb_heredoc;

	nb_heredoc = 0;
	while (list != NULL)
	{
		if (list->type == HERE_DOC)
			nb_heredoc++;
		list = list->next;
	}
	return (nb_heredoc);
}

static void	allocated_pids_array(t_exec *data)
{
	data->pids = ft_calloc(data->nb_cmds, sizeof(pid_t));
}

void	free_struct(t_exec *data)
{
	free_array(data->env_path);
	free(data->cmd_with_path);
	free(data->pids);
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
	data->in_dir = 0;
	data->out_dir = 0;
	data->nb_cmds = get_nb_commands(list);
	data->nb_builtin = get_nb_builtin(list);
	data->nb_heredoc = get_nb_heredoc(list);
	allocated_pids_array(data);
	data->fd_heredoc = ft_calloc(data->nb_heredoc, sizeof(int));
	data->prev_fd = 0;
	data->cmd_with_path = NULL;
	data->cmd = NULL;
	data->paths = NULL;
	data->env_path = NULL;
}
