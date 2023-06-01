/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisa <lisa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:34:32 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/01 14:03:18 by lisa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//ft_dprintf(2, "infile %d\n outfile %d\n new fd[0] %d\n new fd [1] %d\n old fd [0] %d\n old fd [1] %d\n", data->infile, data->outfile, data->new_fd[0], data->new_fd[1], data->old_fd[0], data->old_fd[1]);

/*on peut exit ou return */

/*close old_fd[0] puis je le close sans tout casser dans mon programme ?*/

static int	dup_infiles(t_exec *data)
{
	if (data->infile > 2)
	{
		if (dup2(data->infile, STDIN_FILENO) == -1)
		{
			ft_close(data->new_fd[0]);
			perror("Dup2 issue for an infile");
			return (-1);
		}
		ft_close(data->infile);
	}
	else
	{
		if (dup2(data->old_fd[0], STDIN_FILENO) == -1)
		{
			ft_close(data->new_fd[0]);
			perror("Dup2 issue for fd[0]");
			return (-1);
		}
		ft_close(data->old_fd[0]);
		ft_close(data->new_fd[0]);
	}
	return (0);
}

static int	dup_outfiles(t_exec *data)
{
	if (data->outfile > 2)
	{
		if (dup2(data->outfile, STDOUT_FILENO) == -1)
		{
			ft_close(data->new_fd[0]);
			ft_close(data->infile);
			ft_close(data->old_fd[0]);
			perror("Dup2 issue for an outfile");
			return (-1);
		}
		ft_close(data->outfile);
		ft_close(data->new_fd[1]);
	}
	else
	{
		if (dup2(data->new_fd[1], STDOUT_FILENO) == -1)
		{
			ft_close(data->new_fd[0]);
			perror("Dup2 issue for fd[1]");
			return (-1);
		}
		ft_close(data->new_fd[1]);
	}
	ft_close(data->new_fd[0]);
	return (0);
}

int	dup_files(t_exec *data)
{
	if (dup_infiles(data) == -1)
		return (-1);
	if (dup_outfiles(data) == -1)
		return (-1);
	return (0);
}
