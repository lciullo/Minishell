/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outdata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:32:29 by lciullo           #+#    #+#             */
/*   Updated: 2023/04/26 15:44:12 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	is_outfile_open(t_exec *data)
{
	if (data->outfile > 2)
		close(data->outfile);
}

static	void	manage_outfile(char *outfile, t_exec *data)
{
	is_outfile_open(data);
	data->outfile = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->outfile == -1)
		perror("open outfile");
}

void	loop_for_outfile(t_list *list, t_exec *data)
{
	while (list != NULL && list->type != PIPE)
	{
		if (list->type == OUTFILE)
			manage_outfile(list->data[0], data);
		list = list->next;
	}
}
