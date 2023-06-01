/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisa <lisa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:50:28 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/01 18:11:47 by lisa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	sort_cmd(t_list *list, t_data *parsing, t_exec *data, char **env, t_env *lst)
{
	if (data->nb_block == 1 && parsing->nbr_pipe == 0 && data->nb_builtin == 1)
	{
		if (loop_for_infile(list, data) == -1)
			return (-1);
		if (loop_for_outfile(list, data) == -1)
			return (-1);
		get_builtin_and_exec(list, data, lst);
		return (0);
	}
	else if (data->nb_block >= 1)
	{
		if (get_path_env(data, env) == -1)
			return (-1);
		if (loop_pipe_by_pipe(list, data, env, lst) == -1)
			return (-1);
	}
	return (0);
}

int	execution(t_list *list, char **env, t_data *parsing, t_exec *data, t_env *lst)
{
	if (init_struct(list, data, parsing) == -1)
	{
		perror("Malloc failed in structure initialisation");
		return (-1);
	}
	if (parsing->nbr_here_doc >= 1)
	{
		if (loop_for_heredoc(list, data, &lst) == -1)
		return (-1);
	}
	if (sort_cmd(list, parsing, data, env, lst) == -1)
		return (-1);
	close_for_heredoc(list);
	ft_close(data->infile);
	free_struct(data);
	return (0);
}
