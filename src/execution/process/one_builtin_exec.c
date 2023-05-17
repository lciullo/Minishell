/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_builtin_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:40:57 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/17 11:24:00 by lciullo          ###   ########.fr       */
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

int	one_builtin_exec(char **token, t_exec *data, char **env)
{
	dup_for_one_builtin(data);
	loop_for_builtin(token, data, env);
	return (0);
}

void	get_builtin_and_exec(t_list *list, t_exec *data, char **env)
{
	while (list != NULL)
	{
		if (list->type == BUILTIN)
			one_builtin_exec(list->data, data, env);
		list = list->next;
	}
}
