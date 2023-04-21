/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 09:25:34 by lciullo           #+#    #+#             */
/*   Updated: 2023/04/21 08:56:28 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void heredoc_ctr_c(int signal)
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

static	void	manage_heredoc(char *limiter, t_exec *files)
{
	char	*line;
	int		fd[2];
	int		pid;

	line = NULL;
	if (pipe(fd) == -1)
		exit(1);
	pid = fork();
	if (pid == 0)
	{
		while (1)
		{
			signal(SIGINT, heredoc_ctr_c);
			line = readline("heredoc>");
			signal(SIGINT, new_line);
			//if !line break
			if (ft_strcmp(line, limiter) == 0) 
				break ;
			/*strjoin line puis strjoin \n"*/
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
			free(line);
		}
		files->in = fd[0];
		close(fd[1]);
		exit(1);
	}
	else
		waitpid(pid, NULL, 0);
	return ;
}

void	loop_for_heredoc(t_list *lst, char *limiter)
{
	t_exec	files;
	int		i;
	int		heredoc;

	i = 0;
	heredoc = 0;
	(void)limiter;
	(void)lst;
	(void)heredoc;
	while (lst != NULL)
	{
		while (lst->data[i] != NULL)
		{
			if (ft_strcmp(lst->data[i], "<<") == 0)
			{
				ft_dprintf(1, "find it \n");
				heredoc = 1;
				break ;
			}
			else
				i++;
		}
		if (heredoc == 1)
			manage_heredoc(limiter, &files);
		lst = lst->next;
	}
}
