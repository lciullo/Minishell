/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_builtin_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:40:57 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/22 13:06:55 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	dup_for_one_builtin(t_exec *data)
{
	if (data->infile > 2)
	{
		dup2(data->infile, STDIN_FILENO);
	}
	if (data->outfile > 2)
	{
		dup2(data->outfile, STDOUT_FILENO);
	}
	return (0);
}

int	one_builtin_exec(char **token, t_exec *data, t_env *lst_env)
{
	dup_for_one_builtin(data);
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
}
