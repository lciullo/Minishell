/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisa <lisa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:56:18 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/21 17:39:49 by lisa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	perror("Ft_itoa issue");
	clear_store_heredoc_issue(data);
}

void 	clear_store_heredoc_issue(t_exec *data)
{
	if (data->pids)
		free(data->pids);
	if (data->fd_heredoc)
		free(data->fd_heredoc);
	if (data->env)
		free_array(data->env);
}

void clear_heredoc_end(t_exec *data, t_env **lst, t_list *list, int fd[2])
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
}
void	pipe_heredoc_issue(t_exec *data)
{
	if (data->pids)
		free(data->pids);
	if (data->fd_heredoc)
		free(data->fd_heredoc);
	perror("Pipe issue in heredoc");
}

