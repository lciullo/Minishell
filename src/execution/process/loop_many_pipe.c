/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_many_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:30:04 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/10 11:30:52 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	get_next_pipe(t_list **list)
{
	int		index;

	index = 0;
	while (*list != NULL && (*list)->type != PIPE)
	{
		index++;
		*list = (*list)->next;
	}
	return (index);
}

static	t_list	*list_increment(t_list *list, int index)
{
	int	i;

	i = 0;
	while (list != NULL && i < index)
	{
		list = list->next;
		i++;
	}
	return (list);
}


int	loop_pipe_by_pipe(t_list *list, t_exec	*data, char **env)
{
	int	index;

	index = 0;
	(void)env;
	(void)data;
	while (list != NULL)
	{
		in_exec_print_list(list);
		index = get_next_pipe(&list);
		list = list_increment(list, index);
	}
	return (0);
}