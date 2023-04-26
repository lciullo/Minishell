/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:50:28 by lciullo           #+#    #+#             */
/*   Updated: 2023/04/26 15:50:31 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static	void	init_struct(t_exec *files)
{
	files->infile = 0;
	files->outfile = 0;
}

void	execution(char *line, char **env, t_exec *data)
{
	t_list			*lst;
	t_exec			files;
	char			**cmds;
	char			*delimiter;

	lst = NULL;
	cmds = ft_split(line, ' ');
	lst = ft_lstnew(cmds, 0);
	delimiter = "stop";
	init_struct(&files);
	loop_for_infile(&lst, &files);
	loop_for_heredoc(&lst, delimiter);
	loop_for_builtin(&lst, data);
	loop_for_outfile(&lst, &files);
	(void)env;
}
