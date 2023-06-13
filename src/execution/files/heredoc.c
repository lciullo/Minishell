/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 09:25:34 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/13 10:19:47 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Voir avec Clemence pour le null check du fork et le << stop qui aborte avec fsanitize*/

#include "minishell.h"

static	void	loop_in_child_heredoc(t_exec *data, int *fd, char *delimiter, t_env **lst)
{
	char	*line;

	line = NULL;
	data->expand = 1;
	close(fd[0]);
	close_tab(data);
	while (1)
	{
		signal(SIGINT, heredoc_ctr_c);
		signal(SIGINT, heredoc_new_line);
		line = readline("heredoc> ");
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
			printf("\n");
	}
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

static	int	manage_heredoc(char **delimiter, t_exec *data, t_env **lst, int fd[2])
{
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
		loop_in_child_heredoc(data, fd, *delimiter, lst);
	else
	{
		if (store_heredoc_in_list(delimiter, data, fd) == -1)
			return (-1);
		add_to_tab(data->fd_heredoc, fd[0]);
		waitpid(data->pid_heredoc, NULL, 0);
	}
	return (0);
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
			if (manage_heredoc(&copy->data[0], data, lst, fd) == -1)
			{
				return (-1);
			}
		}
		copy = copy->next;
	}
	return (0);
}
