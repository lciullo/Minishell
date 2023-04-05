/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 09:29:59 by lciullo           #+#    #+#             */
/*   Updated: 2023/03/17 15:50:23 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_struct(t_pipex *data)
{
	data->pid1 = 0;
	data->pid2 = 0;
	data->infile = 0;
	data->outfile = 0;
	data->fd[0] = 0;
	data->fd[1] = 0;
	data->check_infile = 0;
	data->check_outfile = 0;
	data->paths = NULL;
	data->env_path = NULL;
	data->cmds_array = NULL;
	data->cmd = NULL;
}
