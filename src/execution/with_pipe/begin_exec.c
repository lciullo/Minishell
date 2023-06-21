/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisa <lisa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 17:44:33 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/21 20:50:36 by lisa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_token(t_list *list, t_exec *data, char **env, t_env **lst);
static	void	switch_and_close_fds(t_exec *data);
static void	signal_handeler(int signal);
static int	fork_for_execution(t_list *list, t_exec *data, t_env **lst);
static int call_to_launch_exec(t_list *list, t_exec *data, t_env **lst);

int	execution_core(t_list *list, t_exec *data, t_env **lst)
{
	if (data->exec_progress != data->nb_block - 1)
	{
		if (pipe(data->new_fd) == FAILURE)
		{
			perror ("pipe issue of new_fd\n");
			return (FAILURE);
		}
	}
	else
		data->new_fd[1] = STDOUT_FILENO;
	if (fork_for_execution(list, data, lst) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int	execute_token(t_list *list, t_exec *data, char **env, t_env **lst)
{
	if (loop_for_infile(list, data) == FAILURE)
	{
		clear_exec_files_issue(list, lst, data);
		exit(1);
	}
	if (loop_for_outfile(list, data) == FAILURE)
	{
		clear_exec_files_issue(list, lst, data);
		exit(1);
	}
	if (dup_files(data) == FAILURE)
	{
		clear_dup_issue(data, list, lst);
		exit (1);
	}
	ft_close(data->infile);
	launch_exec(data, list, lst, env);
	return (SUCCESS);
}

static void	signal_handeler(int signal)
{
	(void)signal;
	return ;
}

static int call_to_launch_exec(t_list *list, t_exec *data, t_env **lst)
{
	if (execute_token(list, data, data->env, lst) == FAILURE)
	{
		perror("Issue in child process\n");
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	fork_for_execution(t_list *list, t_exec *data, t_env **lst)
{
	signal(SIGQUIT, signal_handeler);
	signal(SIGINT, signal_handeler);
	data->pids[data->nb_pids] = fork();
	if (data->pids[data->nb_pids] == FAILURE)
	{
		perror("Fork issue in few pipe execution_core\n");
		return (FAILURE);
	}
	if (data->pids[data->nb_pids] == 0)
	{
		if (call_to_launch_exec(list, data, lst) == FAILURE)
			return (FAILURE);
	}
	switch_and_close_fds(data);
	data->exec_progress++;
	data->nb_pids++;
	return (SUCCESS);
}

static	void	switch_and_close_fds(t_exec *data)
{
	ft_close(data->infile);
	ft_close(data->new_fd[1]);
	ft_close(data->old_fd[0]);
	data->old_fd[0] = data->new_fd[0];
	data->old_fd[1] = data->new_fd[1];
	return ;
}