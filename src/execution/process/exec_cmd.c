/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:29:59 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/16 09:26:44 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_command(t_list *list, t_exec *data)
{
	while (list != NULL && list->type != PIPE)
	{
		if (list->type == TOKEN)
			data->cmd = list->data[0];
		list = list->next;
	}
	ft_dprintf(2, "%s\n", data->cmd);
}

static char	**token(t_list *list)
{
	while (list != NULL && list->type != PIPE)
	{
		if (list->type == TOKEN)
			return (list->data);
		list = list->next;
	}
	return (NULL);
}

int	execution_core(t_list *list, t_exec *data, char **env)
{
	int	index;

	index = 0;
	if (data->i != data->nb_cmds)
		pipe(data->fd);
	data->pids[index] = fork();
	if (data->pids[index] == 0)
	{
		loop_for_infile(list, data);
		loop_for_outfile(list, data);
		dup_files(data);
		close(data->prev_fd);
		get_command(list, data);
		data->cmd_with_path = check_cmd_acess(data->env_path, data->cmd);
		execve(data->cmd_with_path, token(list), env);
		return (1);
	}
	close(data->fd[1]);
	data->prev_fd = data->fd[0];
	close(data->fd[0]);
	data->i++;
	index++;
	return (0);
}
