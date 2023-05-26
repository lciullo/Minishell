/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 09:25:34 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/26 16:12:48 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_ctr_c(int signal)
{
	(void)signal;
	exit(1);
}

static void	new_line(int signal)
{
	(void)signal;
	ft_dprintf(1, "\n");
}

static	void	loop_in_child_heredoc(t_exec *data, int *fd, char *delimiter, t_env **lst_env)
{
	char	*line;

	line = NULL;
	data->expand = 1;
	close(fd[0]);
	while (1)
	{
		signal(SIGINT, heredoc_ctr_c);
		signal(SIGINT, new_line);
		line = readline("heredoc> ");
		if (line)
		{
			if (!ft_strcmp(line, delimiter))
				break ;
			if (ft_strcmp(line, "$"))
			{
				line = expand(line, lst_env);
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

static	int	manage_heredoc(char **delimiter, t_exec *data, t_env **lst_env)
{
	int	fd[2];

	data->expand = 0;
	if (pipe(fd) == -1)
		exit(1);
	data->pid_heredoc = fork();
	if (data->pid_heredoc == 0)
		loop_in_child_heredoc(data, fd, *delimiter, lst_env);
	close(fd[1]);
	waitpid(data->pid_heredoc, NULL, 0);
	free(*delimiter);
	*delimiter = ft_itoa(fd[0]);
	ft_close(fd[0]);
	return (0);
}

void	loop_for_heredoc(t_list *list, t_exec *data,t_env **lst_env)
{
	t_list	*copy;

	copy = list;
	while (copy != NULL)
	{
		if (copy->type == HERE_DOC)
		{
			manage_heredoc(&copy->data[0], data, lst_env);
		}
		copy = copy->next;
	}
}
