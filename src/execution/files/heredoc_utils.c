/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 08:41:08 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/20 16:06:29 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_tab(int *fd_heredoc, int fd)
{
	int	i;

	i = 0;
	while (fd_heredoc[i] != 0)
	{
		i++;
	}
	fd_heredoc[i] = fd;
}

void	heredoc_ctr_c(int signal)
{
	(void)signal;
	g_exit_status = 130;
	close(0);
}

void	heredoc_new_line(int signal)
{
	(void)signal;
	ft_dprintf(1, "\n");
}
