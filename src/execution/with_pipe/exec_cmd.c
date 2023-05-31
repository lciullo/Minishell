/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:29:59 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/30 16:47:25 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_token(t_list *list, t_exec *data, char **env, t_env *lst_env)
{
	if (loop_for_infile(list, data) == -1)
	{
		clear_files_issu(data, list, lst_env);
		exit (1);
	}
	if (loop_for_outfile(list, data) == -1)
	{
		clear_files_issu(data, list, lst_env);
		exit(1);
	}
	if (dup_files(data) == -1)
	{
		clear_dup_issu(data, list, lst_env);
		exit (1);
	}
	ft_close(data->infile);
	launch_exec(data, list, lst_env, env);
	return (0);
}

int	execution_core(t_list *list, t_exec *data, char **env, t_env *lst_env)
{
	if (data->i != data->nb_cmds - 1)
	{
		pipe(data->new_fd);
	}
	else
		data->new_fd[1] = STDOUT_FILENO;
	data->pids[data->index] = fork();
	if (data->pids[data->index] == 0)
	{
		execute_token(list, data, env, lst_env);
		exit (1);
	}
	ft_close(data->new_fd[1]);
	ft_close(data->old_fd[0]);
	data->old_fd[0] = data->new_fd[0];
	data->old_fd[1] = data->new_fd[1];
	data->i++;
	data->index++;
	return (0);
}
