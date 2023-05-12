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

static	void	is_infile_open(t_exec *data)
{
	if (data->infile > 2)
		close(data->infile);
}

static	int	manage_infile(char *infile, t_exec *data)
{
	is_infile_open(data);
	data->infile = open(infile, O_RDONLY, 0644);
	if (data->infile == -1)
	{
		perror("open infile");
		return (-1);
	}
	return (0);
}

int	loop_for_infile(t_list *list, t_exec *data)
{
	while (list != NULL && list->type != PIPE)
	{
		if (list->type == INFILE)
		{
			if (manage_infile(list->data[0], data) == -1)
				return (-1);
		}
		list = list->next;
	}
	return (0);
}
