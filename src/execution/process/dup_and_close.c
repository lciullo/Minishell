/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_and_close.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:34:32 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/25 13:11:39 by lciullo          ###   ########.fr       */
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
			ft_close(data->infile);
			exit (1);
		}
		ft_close(data->infile);
	}
	else
	{
		if (dup2(data->old_fd[0], STDIN_FILENO) == -1)
		{
			exit(1);
		}
		ft_close(data->old_fd[0]);
		ft_close(data->new_fd[0]);
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
		ft_close(data->outfile);
		ft_close(data->new_fd[1]);
	}
	else
	{
		if (dup2(data->new_fd[1], STDOUT_FILENO) == -1)
		{
			exit(1);
		}
		ft_close(data->new_fd[1]);
	}
	ft_close(data->new_fd[0]);
	return (0);
}

/*int	dup_files(t_exec *data)
{
	ft_dprintf(2, "\nin dup files\n");
	ft_dprintf(2, "infile %d\n outfile %d\n new fd[0] %d\n new fd [1] %d\n old fd [0] %d\n old fd [1] %d\n", data->infile, data->outfile, data->new_fd[0], data->new_fd[1], data->old_fd[0], data->old_fd[1]);
	if (data->infile > 2)
	{
		if (dup2(data->infile, STDIN_FILENO) == -1)
		{
			ft_dprintf(2, "infile issu\n");
			ft_close(data->infile);
			exit (1);
		}
		ft_close(data->infile);
		ft_close(data->new_fd[0]);
	}
	else
	{
		ft_dprintf(2, "old fd[0]\n");
		if (dup2(data->old_fd[0], STDIN_FILENO) == -1)
		{
			ft_dprintf(2, "fd[0] issu \n");
			exit(1);
		}
		ft_close(data->old_fd[0]);
	}
	if (data->outfile > 2)
	{
		ft_dprintf(2, "outfile\n");
		if (dup2(data->outfile, STDOUT_FILENO) == -1)
		{
			ft_dprintf(2, "outfile issu\n");
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
		ft_dprintf(2, "new fd[1]\n");
		if (dup2(data->new_fd[1], STDOUT_FILENO) == -1)
		{
			ft_dprintf(2, "issu fd[1]\n");
			exit(1);
		}
		ft_close(data->new_fd[1]);
	}
	ft_close(data->new_fd[0]);
	return (0);
}*/