/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:50:28 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/02 15:10:39 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	init_struct(t_exec *files)
{
	files->infile = 0;
	files->outfile = 0;
}

static int	loop_for_token(t_list **lst, t_exec *data, char **env)
{
	if (is_builtin(lst))
		loop_for_builtin(lst, data, env);
	else
		ft_dprintf(1, "is not a builtin");
	return (0);
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
	loop_for_token(&lst, data, env);
	loop_for_outfile(&lst, &files);
}
