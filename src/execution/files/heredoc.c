/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 09:25:34 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/09 10:26:00 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_ctr_c(int signal)
{
	(void)signal;
	//penser a free
	exit(1);
}

static void	new_line(int signal)
{
	(void)signal;
	ft_dprintf(1, "\n");
}

static	void	loop_in_child_heredoc(t_exec *heredoc, int *fd, char *delimiter)
{
	char	*line;

	line = NULL;
	heredoc->expand = 1;
	while (1)
	{
		signal(SIGINT, heredoc_ctr_c);
		line = readline("heredoc>");
		signal(SIGINT, new_line);
		//if !line break
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		/*strjoin line puis strjoin \n"*/
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
	}
	free(line);
	//data->in = fd[0];
	close(fd[1]);
	//expand
	exit(1);
}

static	void	manage_heredoc(char *delimiter)
{
	int		pid;
	int		fd[2];
	t_exec	heredoc;

	pid = 0;
	heredoc.expand = 0;
	(void)delimiter;
	/*if (ft_strchr(delimiter, -''') || ft_strchr(delimiter, -'"'))
	{
		heredoc->expand = 1;
		//trim delimiter
	}*/
	if (pipe(fd) == -1)
		exit(1);
	pid = fork();
	if (pid == 0)
		loop_in_child_heredoc(&heredoc, fd, delimiter);
	else
		waitpid(pid, NULL, 0);
	return ;
}

void	loop_for_heredoc(t_list **lst, char *delimiter)
{
	int		i;
	t_list	*head;

	i = 0;
	(void)delimiter;
	head = *lst;
	while (head != NULL)
	{
		while (head->data[i] != NULL)
		{
			if (ft_strcmp(head->data[i], "<<") == 0)
			{
				manage_heredoc(delimiter);
				break ;
			}
			else
				i++;
		}
		head = head->next;
	}
}
