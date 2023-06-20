/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 17:44:33 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/20 19:15:29 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_token(t_list *list, t_exec *data, char **env, t_env **lst)
{
	if (loop_for_infile(list, data) == -1)
	{	
		clear_exec_files_issu(list, lst, data);
		exit(1);
	}
	if (loop_for_outfile(list, data) == -1)
	{
		clear_exec_files_issu(list, lst, data);
		exit(1);
	}
	if (dup_files(data) == -1)
	{
		clear_dup_issue(data, list, lst);
		exit (1);
	}
	ft_close(data->infile);
	launch_exec(data, list, lst, env);
	return (0);
}

static	void	switch_and_close_fds(t_exec *data)
{
	ft_close(data->new_fd[1]);
	ft_close(data->old_fd[0]);
	data->old_fd[0] = data->new_fd[0];
	data->old_fd[1] = data->new_fd[1];
	return ;
}

static void	signal_handeler(int signal)
{
	(void)signal;
	return ;
}

int	execution_core(t_list *list, t_exec *data, t_env **lst)
{
	if (data->exec_progress != data->nb_block - 1)
	{
		if (pipe(data->new_fd) == -1)
		{
			ft_dprintf(2, "pipe issu of new_fd\n");
			return (-1);
		}
	}
	else
		data->new_fd[1] = STDOUT_FILENO;
	signal(SIGQUIT, signal_handeler);
	signal(SIGINT, signal_handeler);
	data->pids[data->nb_pids] = fork();
	if (data->pids[data->nb_pids] == -1)
	{
		perror("Fork issu in few pipe execution_core\n");
		return (-1);
	}
	if (data->pids[data->nb_pids] == 0)
	{
		if (execute_token(list, data, data->env, lst) == -1)
		{
			ft_dprintf(2, "in execution core\n");
			return (-1);
		}
	}
	close_for_heredoc(list);
	ft_close(data->infile);
	switch_and_close_fds(data);
	data->exec_progress++;
	data->nb_pids++;
	return (0);
}
