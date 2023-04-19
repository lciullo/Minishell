/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 09:25:34 by lciullo           #+#    #+#             */
/*   Updated: 2023/04/19 11:43:27 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	manage_heredoc(char *limiter)
{
	char	*line;
	char	*tmp;
	int		fd[2];

	line = NULL;
	tmp = "heredoc> ";
	if (pipe(fd) == -1)
		exit(1);
	while (1)
	{
		line = readline(tmp);
		if (ft_strcmp(line, limiter) == 0)
			break ;
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	//manage the infile here
	close(fd[1]);
}

void	loop_for_heredoc(t_list *lst, char *limiter)
{
	int	i;
	int	heredoc;

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
		lst = lst->next;
		if (heredoc == 1)
			manage_heredoc(limiter);
	}
}
