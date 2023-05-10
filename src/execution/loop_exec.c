/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:50:28 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/10 14:51:04 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
===============
Type
===============
Infile = 0
Token = 1
Outfile = 2
Pipe = 3
sort_token_and_builtin(list->data, data, env);
*/
static	int	sort_token_and_builtin(char **token, t_exec *data, char **env)
{
	if (data->nb_cmds == 1 && is_builtin(token))
 		one_builtin_exec(token, data, env);
 	else if (data->nb_cmds > 1)
 	{
 		if (is_builtin(token))
 			loop_for_builtin(token, data, env);
 	}
 	return (0);
}

void	execution(t_list *list, char **env, t_exec *data)
{
	init_struct(data);
	loop_pipe_by_pipe(list, data, env);
}
