/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:34:32 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/16 15:18:35 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*on peut exit ou return */

static	void	ft_close(int fd)
{
	if (fd > 2)
		close(fd);
}

int	dup_files(t_exec *data)
{
	if (data->infile > 2)
	{
		dup2(data->infile, STDIN_FILENO);
		close(data->infile);
		ft_close(data->old_fd[0]);
	}
	else
	{
		dup2(data->old_fd[0], STDIN_FILENO);
		ft_close(data->old_fd[0]);
	}
	if (data->outfile > 2)
	{
		dup2(data->outfile, STDOUT_FILENO);
		close(data->outfile);
		ft_close(data->new_fd[1]);
	}
	else
	{
		dup2(data->new_fd[1], STDOUT_FILENO);
		ft_close(data->new_fd[1]);
	}
	ft_close(data->new_fd[0]);
	return (0);
}
