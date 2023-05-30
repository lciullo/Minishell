/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:46:51 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/30 11:22:56 by lciullo          ###   ########.fr       */
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
		ft_close(data->new_fd[0]);
		i++;
	}
	return (0);
}

int	loop_pipe_by_pipe(t_list *list, t_exec	*data, char **env, t_env *lst_env)
{
	int	index;

	index = 0;
	data->old_fd[0] = STDIN_FILENO;
	data->new_fd[1] = STDOUT_FILENO;
	while (list != NULL)
	{
		execution_core(list, data, env, lst_env);
		index = get_next_pipe(list);
		list = list_increment(&list, index + 1);
	}
	if (data->in_dir > 1)
			ft_close(data->infile);
		else
			ft_close(data->old_fd[0]);
		if (data->out_dir > 1)
			ft_close(data->outfile);
		else
			ft_close(data->new_fd[1]);
	ft_close(data->new_fd[0]);
	wait_pids(data);
	data->index = 0;
	return (0);
}
