/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:56:18 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/31 14:37:12 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	close_for_heredoc(t_list *list)
{
	while (list != NULL)
	{
		if (list->type == HERE_DOC)
		{
			ft_close(ft_atoi(list->data[0]));
		}
		list = list->next;
	}
	return (0);
}

void	fork_issue_heredoc(t_exec *data, int fd[2])
{
	ft_close(fd[0]);
	ft_close(fd[1]);
	if (data->pids)
		free(data->pids);
	if (data->fd_heredoc)
		free(data->fd_heredoc);
	perror("Fork issue in heredoc");
}

void	itoa_heredoc_issue(t_exec *data, int fd[2])
{
	ft_close(fd[0]);
	ft_close(fd[1]);
	if (data->pids)
		free(data->pids);
	if (data->fd_heredoc)
		free(data->fd_heredoc);
	perror("Ft_itoa issue");
	waitpid(data->pid_heredoc, NULL, 0);
}

void	pipe_heredoc_issue(t_exec *data)
{
	if (data->pids)
		free(data->pids);
	if (data->fd_heredoc)
		free(data->fd_heredoc);
	perror("Pipe issue in heredoc");
}

void	close_tab(t_exec *data)
{
	int	i;

	i = 0;
	while (i < data->nb_heredoc)
	{
		ft_close(data->fd_heredoc[i]);
		i++;
	}
}
