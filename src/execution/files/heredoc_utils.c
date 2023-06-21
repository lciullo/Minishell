/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisa <lisa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 08:41:08 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/21 12:42:34 by lisa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_tab_heredoc(int *fd_heredoc, int fd)
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
