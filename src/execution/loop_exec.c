/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:50:28 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/11 16:42:28 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
sort_token_and_builtin(list->data, data, env);

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
}*/

static void	sort_token(t_list *list, t_data *parsing, t_exec *data, char **env)
{
	if (data->nb_cmds >= 1)
	{
		get_path_env(data, env);
		loop_pipe_by_pipe(list, parsing, data, env);
	}
	return ;
}

void	execution(t_list *list, char **env, t_data *parsing, t_exec *data)
{
	init_struct(list, data);
	sort_token(list, parsing, data, env);
}
