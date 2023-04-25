/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisa <lisa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 09:29:41 by lciullo           #+#    #+#             */
/*   Updated: 2023/04/25 10:44:50 by lisa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(char *line, char **env, t_exec *data)
{
	t_list			*lst;
	char			**cmds;
	char			*delimiter;

	lst = NULL;
	cmds = ft_split(line, ' ');
	lst = ft_lstnew(cmds, 0);
	delimiter = "stop";
	loop_for_infile(&lst);
	loop_for_heredoc(&lst, delimiter);
	loop_for_builtin(&lst, data);
	(void)env;
}
