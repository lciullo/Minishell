/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_pipe_by_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:30:04 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/16 09:18:34 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	get_next_pipe(t_list *list)
{
	int		index;

	index = 0;
	while (list != NULL && list->type != PIPE)
	{
		index++;
		list = list->next;
	}
	return (index);
}

static	t_list	*list_increment(t_list **list, int index)
{
	while (*list && index > 0)
	{
		index--;
		*list = (*list)->next;
	}
	return (*list);
}

static	int	wait_pids(t_exec *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmds)
	{
		waitpid(data->pids[i], NULL, 0);
		i++;
	}
	return (0);
}

int	loop_pipe_by_pipe(t_list *list, t_data *parsing, t_exec	*data, char **env)
{
	int	index;

	index = 0;
	(void)parsing;
	while (list != NULL)
	{
		execution_core(list, data, env);
		index = get_next_pipe(list);
		list = list_increment(&list, index + 1);
	}
	wait_pids(data);
	return (0);
}
