/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 09:29:41 by lciullo           #+#    #+#             */
/*   Updated: 2023/04/19 10:48:39 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(char *line, char **env)
{
	t_list	*lst;
	char	**cmds;
	char	*limiter;

	lst = NULL;
	cmds = ft_split(line, ' ');
	lst = ft_lstnew(cmds, 0);
	limiter = "stop";
	loop_for_heredoc(lst, limiter);
	(void)env;
}
