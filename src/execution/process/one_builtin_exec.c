/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_builtin_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:40:57 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/25 14:34:55 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	dup_for_one_builtin(t_exec *data)
{
	if (data->infile > 2)
	{
		data->in_dir = 1;
		if (dup2(data->infile, STDIN_FILENO) == -1)
		{
			ft_dprintf(2, "dup infile issu\n");
			return (-1);
		}
		ft_close(data->infile);
	}
	if (data->outfile > 2)
	{
		data->out_dir = 1;
		if (dup2(data->outfile, STDOUT_FILENO) == -1)
		{
			ft_dprintf(2, "dup outfile issu\n");
			return (-1);
		}
		ft_close(data->outfile);
	}
	return (0);
}

int	one_builtin_exec(char **token, t_exec *data, t_env *lst_env)
{
	if (dup_for_one_builtin(data) == -1)
		return (-1);
	loop_for_builtin(token, data, lst_env);
	return (0);
}

void	get_builtin_and_exec(t_list *list, t_exec *data, t_env *lst_env)
{
	while (list != NULL)
	{
		if (list->type == BUILTIN)
			one_builtin_exec(list->data, data, lst_env);
		list = list->next;
	}
	return ;
}
