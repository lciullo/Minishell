/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:46:51 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/06 16:44:46 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	get_next_pipe(t_list *list)
{
	int		len_between_pipe;

	len_between_pipe = 0;
	while (list != NULL && list->type != PIPE)
	{
		len_between_pipe++;
		list = list->next;
	}
	return (len_between_pipe);
}

static	t_list	*list_increment(t_list **list, int len_between_pipe)
{
	while (*list && len_between_pipe > 0)
	{
		len_between_pipe--;
		*list = (*list)->next;
	}
	return (*list);
}

static	int	wait_pids(t_exec *data)
{
	int	i;

	i = 0;
	while (i < data->nb_block)
	{
		waitpid(data->pids[i], NULL, 0);
		ft_close(data->new_fd[0]);
		i++;
	}
	return (0);
}

int	loop_pipe_by_pipe(t_list *list, t_exec	*data, char **env, t_env **lst)
{
	int	len_between_pipe;

	len_between_pipe = 0;
	data->old_fd[0] = STDIN_FILENO;
	data->new_fd[1] = STDOUT_FILENO;
	while (list != NULL)
	{
		execution_core(list, data, env, lst);
		len_between_pipe = get_next_pipe(list);
		list = list_increment(&list, len_between_pipe + 1);
	}
	close_between_commands(data);
	wait_pids(data);
	data->nb_pids = 0;
	return (0);
}
