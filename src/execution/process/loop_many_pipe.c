/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_many_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:30:04 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/10 17:38:32 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static void	exec_print_list(t_list *lst)
{
	int	i;

	i = 0;
	ft_dprintf(1, "IN PRINT LIST\n");
	ft_dprintf(1, "===============================\n");
	while (lst != NULL && lst->type != PIPE)
	{
		i = 0;
		while (lst->data[i] != NULL)
		{
			ft_dprintf(1, "row[%s]\n", lst->data[i]);
			i++;
		}
		lst = lst->next;
	}
	ft_dprintf(1, "===============================\n");
}*/

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

int	loop_pipe_by_pipe(t_list *list, t_exec	*data, char **env)
{
	int	index;

	index = 0;
	(void)env;
	(void)data;
	while (list != NULL)
	{
		//print_list(list);
		loop_for_infile(list, data);
		loop_for_outfile(list, data);
		index = get_next_pipe(list);
		list = list_increment(&list, index + 1);
	}
	if (data->infile > 2)
		close(data->infile);
	if (data->outfile > 2)
		close(data->outfile);
	return (0);
}
