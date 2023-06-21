/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:57:20 by lciullo           #+#    #+#             */
/*   Updated: 2023/04/26 15:27:49 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	is_infile_open(t_exec *data);
static	int		manage_infile(char *infile, t_exec *data);
static void		in_zero_fd(t_exec *data, int fd);

int	loop_for_infile(t_list *list, t_exec *data)
{
	while (list != NULL && list->type != PIPE)
	{
		if (list->type == INFILE)
		{
			if (manage_infile(list->data[0], data) == FAILURE)
				return (FAILURE);
		}
		if (list->type == HERE_DOC)
		{
			is_infile_open(data);
			data->infile = ft_atoi(list->data[0]);
			in_zero_fd(data, ft_atoi(list->data[0]));
			data->in_dir++;
		}
		list = list->next;
	}
	return (SUCCESS);
}

static	int	manage_infile(char *infile, t_exec *data)
{
	is_infile_open(data);
	data->infile = open(infile, O_RDONLY, 0644);
	data->in_dir++;
	if (data->infile == FAILURE)
	{
		perror("Permission denied");
		return (FAILURE);
	}
	return (SUCCESS);
}

static	void	is_infile_open(t_exec *data)
{
	if (data->infile > 2)
		close(data->infile);
}

static void		in_zero_fd(t_exec *data, int fd)
{
	int	i;

	i = 0;
	while (i < data->nb_heredoc)
	{
		if (data->fd_heredoc[i] == fd)
			data->fd_heredoc[i] = 0;
		i++;
	}
}
