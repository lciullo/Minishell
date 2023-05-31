/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:58:37 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/31 16:44:15 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close(int fd)
{
	if (fd > 2)
		close(fd);
}

void	close_cmd_not_found(t_exec *data)
{
	if (data->in_dir > 1)
	{
		close(data->old_fd[0]);
		close(data->old_fd[1]);
		close(data->infile);
	}
	else
	{
		close(data->old_fd[0]);
		close(data->new_fd[0]);
		close(data->infile);
	}
	if (data->out_dir > 1)
		close(data->outfile);
	else
	{
		close(data->new_fd[1]);
		close(data->old_fd[1]);
		close(data->outfile);
	}
	ft_close(data->infile);
}

void	close_between_commands(t_exec *data)
{
	if (data->in_dir > 1)
		ft_close(data->infile);
	else
		ft_close(data->old_fd[0]);
	if (data->out_dir > 1)
		ft_close(data->outfile);
	else
		ft_close(data->new_fd[1]);
	ft_close(data->new_fd[0]);
}

void	close_all_fds(t_exec *data)
{
	
}