/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:29:59 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/17 09:53:54 by lciullo          ###   ########.fr       */
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

int	execution_core(t_list *list, t_exec *data, char **env)
{
	if (data->i != data->nb_cmds - 1)
		pipe(data->new_fd);
	else
		data->new_fd[1] = STDOUT_FILENO;
	data->pids[data->index] = fork();
	if (data->pids[data->index] == 0)
	{
		if (loop_for_infile(list, data) == -1)
			exit(1);
		if (loop_for_outfile(list, data) == -1)
			exit(1);
		dup_files(data);
		get_command(list, data);
		data->cmd_with_path = check_cmd_acess(data->env_path, data->cmd);
		if (!data->cmd_with_path)
		{	
			perror("command");
			exit(1);
		}
		execve(data->cmd_with_path, token(list), env);
		perror("execve");
		exit (1);
	}
	ft_close(data->old_fd[0]);
	ft_close(data->new_fd[1]);
	data->old_fd[0] = data->new_fd[0];
	data->old_fd[1] = data->new_fd[1];
	data->i++;
	data->index++;
	return (0);
}
