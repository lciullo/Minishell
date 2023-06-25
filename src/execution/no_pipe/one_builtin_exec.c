/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_builtin_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 18:13:24 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/25 19:07:27 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	dup_for_one_builtin(t_exec *data, t_env **lst, t_list *list);
static	int	to_fork(char **token);
static int	execute_builtin_in_child(char **token, t_exec *data, \
				t_env **lst, t_list *list);

void	get_builtin_and_exec(t_list *list, t_exec *data, t_env **lst)
{
	while (list != NULL)
	{
		if (list->type == BUILTIN)
			one_builtin_exec(list->data, data, lst, list);
		list = list->next;
	}
	return ;
}

int	one_builtin_exec(char **token, t_exec *data, t_env **lst, t_list *list)
{
	if (!token[0])
		return (FAILURE);
	if (to_fork(token) == TRUE)
		execute_builtin_in_child(token, data, lst, list);
	else
	{
		loop_for_builtin(token, data, lst);
		ft_close(data->infile);
		ft_close(data->outfile);
		close_tab_heredoc(data);
	}
	return (SUCCESS);
}

static	int	dup_for_one_builtin(t_exec *data, t_env **lst, t_list *list)
{
	if (data->infile > 2)
	{
		if (dup2(data->infile, STDIN_FILENO) == FAILURE)
		{
			clear_dup_issue_builtin(data, list, lst);
			perror("dup infile issue");
			exit (1);
		}
		ft_close(data->infile);
	}
	if (data->outfile > 2)
	{
		if (dup2(data->outfile, STDOUT_FILENO) == FAILURE)
		{
			clear_dup_issue_builtin(data, list, lst);
			perror("dup outfile issue");
			exit (1);
		}
		ft_close(data->outfile);
	}
	return (SUCCESS);
}

static	int	to_fork(char **token)
{
	if (ft_strcmp(token[0], "echo") == 0)
		return (TRUE);
	if (ft_strcmp(token[0], "pwd") == 0)
		return (TRUE);
	if (ft_strcmp(token[0], "env") == 0)
		return (TRUE);
	else if (ft_strcmp(token[0], "export") == 0)
	{
		if (!token[1])
			return (TRUE);
		else
			return (FALSE);
	}
	else if (ft_strcmp(token[0], "cd") == 0)
		return (FALSE);
	else if (ft_strcmp(token[0], "exit") == 0)
		return (FALSE);
	else if (ft_strcmp(token[0], "unset") == 0)
		return (FALSE);
	else if (ft_strcmp(token[0], "env") == 0)
		return (FALSE);
	return (FAILURE);
}

static int	execute_builtin_in_child(char **token, t_exec *data, \
		t_env **lst, t_list *list)
{
	int	pid;
	int	status;

	status = 0;
	pid = fork();
	if (pid == FAILURE)
	{
		perror("Fork issue in one builtin execution\n");
		return (FAILURE);
	}
	if (pid == 0)
	{
		dup_for_one_builtin(data, lst, list);
		loop_for_builtin(token, data, lst);
		clear_in_child(data, lst, list);
		exit (g_exit_status);
	}
	if (waitpid(pid, &status, 0) == FAILURE)
		g_exit_status = 1;
	else if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	ft_close(data->infile);
	ft_close(data->outfile);
	return (SUCCESS);
}
