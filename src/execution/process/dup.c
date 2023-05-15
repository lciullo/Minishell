/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:34:32 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/15 15:25:51 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dup_files(t_exec *data)
{
	dup2(data->prev_fd, STDIN_FILENO);
	dup2(data->fd[1], STDOUT_FILENO);
	if (data->infile_opened == true)
		dup2(data->infile, STDIN_FILENO);
	if (data->outfile_opened == true)
		dup2(data->outfile, STDOUT_FILENO);
	return (0);
}
