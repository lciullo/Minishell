/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:50:28 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/26 16:51:34 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	sort_cmd(t_list *list, t_data *parsing, t_exec *data, char **env, t_env *lst_env)
{
	(void)parsing;
	if (data->nb_cmds == 1 && parsing->nbr_pipe == 0 && data->nb_builtin == 1)
	{
		if (loop_for_infile(list, data) == -1)
			return (0);
		if (loop_for_outfile(list, data) == -1)
			return (0);
		get_builtin_and_exec(list, data, lst_env);
		ft_close(data->infile);
		ft_close(data->outfile);
	}
	if (data->nb_cmds >= 1)
	{
		get_path_env(data, env);
		loop_pipe_by_pipe(list, data, env, lst_env);
	}
	return (0);
}

static int	close_for_heredoc(t_list *list)
{
	while (list != NULL)
	{
		if (list->type == HERE_DOC)
		{
			ft_close(ft_atoi(list->data[0]));
		}
		list = list->next;
	}
	return (0);
}

void	execution(t_list *list, char **env, t_data *parsing, t_exec *data, t_env *lst_env)
{
	init_struct(list, data);
	loop_for_heredoc(list, data, &lst_env);
	sort_cmd(list, parsing, data, env, lst_env);
	close_for_heredoc(list);
}
