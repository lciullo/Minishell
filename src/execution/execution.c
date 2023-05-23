/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:50:28 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/23 10:21:35 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sort_cmd(t_list *list, t_data *parsing, t_exec *data, char **env, t_env *lst_env)
{
	if (data->nb_cmds == 1 && parsing->nbr_pipe == 0 && data->nb_builtin == 1)
	{
		if (loop_for_infile(list, data) == -1)
			return ;
		if (loop_for_outfile(list, data) == -1)
			return ;
		get_builtin_and_exec(list, data, lst_env);
	}
	else if (data->nb_cmds >= 1)
	{
		get_path_env(data, env);
		loop_pipe_by_pipe(list, data, env, lst_env);
	}
	return ;
}

void	execution(t_list *list, char **env, t_data *parsing, t_exec *data, t_env *lst_env)
{
	init_struct(list, data);
	loop_for_heredoc(list, data);
	sort_cmd(list, parsing, data, env, lst_env);
}
