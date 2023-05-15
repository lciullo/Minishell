/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:29:59 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/15 15:32:56 by lciullo          ###   ########.fr       */
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

int	execution_core(t_list *list, t_data *parsing, t_exec *data, char **env)
{
	int		pid;
	(void)parsing;

	pid = 0;
	if (data->i != data->nb_cmds)
		pipe(data->fd);
	pid = fork();
	if (pid == 0)
	{
		loop_for_infile(list, data);
		loop_for_outfile(list, data);
		dup_files(data);
		get_command(list, data);
		data->cmd_with_path = check_cmd_acess(data->env_path, data->cmd);
		if (!data->cmd_with_path)
			return (-1);
		execve(data->cmd_with_path, token(list), env);
	}
	close(data->fd[1]);
	data->prev_fd = data->fd[0];
	data->i++;
	return (0);
}
