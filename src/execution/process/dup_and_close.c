/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_and_close.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:34:32 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/18 16:18:19 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*on peut exit ou return */

void	ft_close(int fd)
{
	if (fd > 2)
		close(fd);
}

int	dup_files(t_exec *data)
{
	if (data->infile > 2)
	{
		if (dup2(data->infile, STDIN_FILENO) == -1)
		{
			puts("infile issu");
			exit (1);
		}
		close(data->infile);
		ft_close(data->old_fd[0]);
	}
	else
	{
		if (dup2(data->old_fd[0], STDIN_FILENO) == -1)
			exit(1);
		ft_close(data->old_fd[0]);
	}
	if (data->outfile > 2)
	{
		if (dup2(data->outfile, STDOUT_FILENO) == -1)
		{
			ft_close(data->new_fd[0]);
			ft_close(data->infile);
			ft_close(data->old_fd[0]);
			exit(1);
		}
		close(data->outfile);
		ft_close(data->new_fd[1]);
	}
	else
	{
		if (dup2(data->new_fd[1], STDOUT_FILENO) == -1)
			exit(1);
		ft_close(data->new_fd[1]);
	}
	ft_close(data->new_fd[0]);
	return (0);
}
