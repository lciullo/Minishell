/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 09:25:34 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/20 16:46:43 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Voir avec Clemence pour le null check du fork et le << stop qui aborte avec fsanitize*/

#include "minishell.h"

static	void	loop_in_child_heredoc(t_exec *data, int *fd, char *delimiter, t_env **lst, t_list *list)
{
	char	*line;

	line = NULL;
	//data->expand = 1;
	close(fd[0]);
	close_tab(data);
	g_exit_status = 0;
	while (g_exit_status == 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, heredoc_ctr_c);
		line = readline("heredoc> ");
		signal(SIGINT, heredoc_new_line);
		if (line)
		{
			if (!ft_strcmp(line, delimiter))
				break ;
			if (ft_strcmp(line, "$") && data->quote_here_doc == 0)
			{
				line = expand(line, *lst);
			}
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
			free(line);
		}
		else
		{
			if (g_exit_status == 130)
			{
				if (lst)
					ft_lstclear_env(lst, free);
				if (list)
					ft_lstclear(&list, free);
				if (data->env)
					free_array(data->env);
				if (data->pids)
					free(data->pids);
				if (data->fd_heredoc)
					free(data->fd_heredoc);
				close(fd[1]);
				exit (g_exit_status);
			}
			ft_dprintf(2, "here-document at line %d delimited by end-of-file [%s]\n", line, delimiter);
			free(line);
			g_exit_status = 131;
			if (lst)
				ft_lstclear_env(lst, free);
			if (list)
				ft_lstclear(&list, free);
			if (data->env)
				free_array(data->env);
			if (data->pids)
				free(data->pids);
			if (data->fd_heredoc)
				free(data->fd_heredoc);
			close(fd[1]);
			exit (g_exit_status);
		}
	}
	if (lst)
		ft_lstclear_env(lst, free);
	if (list)
		ft_lstclear(&list, free);
	if (data->env)
		free_array(data->env);
	if (data->pids)
		free(data->pids);
	if (data->fd_heredoc)
		free(data->fd_heredoc);
	close(fd[1]);
	exit(1);
}

static int	store_heredoc_in_list(char **delimiter, t_exec *data, int *fd)
{
	ft_close(fd[1]);
	free(*delimiter);
	*delimiter = ft_itoa(fd[0]);
	if (!*delimiter)
	{
		itoa_heredoc_issue(data, fd);
		return (-1);
	}
	return (0);
}

static	int	manage_heredoc(char **delimiter, t_exec *data, t_env **lst, int fd[2], t_list *list)
{
	int	status;

	status = 0;
	if (pipe(fd) == -1)
	{
		pipe_heredoc_issue(data);
		return (-1);
	}
	data->pid_heredoc = fork();
	if (data->pid_heredoc == -1)
	{
		fork_issue_heredoc(data, fd);
		return (-1);
	}
	if (data->pid_heredoc == 0)
	{
		loop_in_child_heredoc(data, fd, *delimiter, lst, list);
	}
	else
	{
		if (store_heredoc_in_list(delimiter, data, fd) == -1)
			return (-1);
		add_to_tab(data->fd_heredoc, fd[0]);
		if (waitpid(data->pid_heredoc, &status, WUNTRACED) == -1)
			g_exit_status = WEXITSTATUS(status);
		else if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
	}
	return (g_exit_status);
}

int	loop_for_heredoc(t_list *list, t_exec *data, t_env **lst)
{
	t_list	*copy;
	int		fd[2];

	copy = list;
	fd[0] = 0;
	fd[1] = 1;
	while (copy != NULL)
	{
		if (copy->type == HERE_DOC)
		{
			data->quote_here_doc = copy->quote_here_doc;
			g_exit_status = manage_heredoc(&copy->data[0], data, lst, fd, list);
			if (g_exit_status == -1 || g_exit_status == 131 || g_exit_status == 130)
				return (g_exit_status);
		}
		copy = copy->next;
	}
	return (g_exit_status);
}
