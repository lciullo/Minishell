/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_close.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 09:27:14 by lciullo           #+#    #+#             */
/*   Updated: 2023/03/17 15:54:20 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_files(t_pipex *data)
{
	if (data->fd[0])
		close(data->fd[0]);
	if (data->fd[1])
		close(data->fd[1]);
	if (data->check_infile == 0)
		close(data->infile);
	if (data->check_outfile == 0)
		close(data->outfile);
}

void	free_env_path(t_pipex *data)
{
	int	i;

	i = 0;
	while (data->env_path[i])
	{
		free(data->env_path[i]);
		i++;
	}
	free(data->env_path);
}

void	free_cmds_and_paths(t_pipex *data)
{
	int	i;

	i = 0;
	while (data->cmds_array[i])
	{
		free(data->cmds_array[i]);
		i++;
	}
	free(data->cmds_array);
	free(data->cmd);
}
