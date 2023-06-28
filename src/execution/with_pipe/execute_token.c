/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:17:14 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/25 19:52:35 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	finish_by_cmd_not_found(t_exec *data, t_list *list, \
				t_env **lst, int empty);
static int	get_empty_type(t_list *list);
static char	**get_command(t_list *list);

int	execution_of_token(t_exec *data, t_list *list, t_env **lst)
{
	int	empty;

	empty = get_empty_type(list);
	data->cmd_with_path = check_cmd_access(data->env_path, data->cmd, empty);
	if (!data->cmd_with_path)
	{
		g_exit_status = finish_by_cmd_not_found(data, list, lst, empty);
		exit(g_exit_status);
	}
	close_tab_heredoc(data);
	if (data->cmd_with_path != NULL && \
		is_executable(data->cmd_with_path, data, list, lst) == SUCCESS)
	{
		g_exit_status = 1;
		execve(data->cmd_with_path, get_command(list), data->env);
		clear_execve_issue(data, list, lst);
		exit(g_exit_status);
	}
	if (data->env)
		free_array(data->env);
	if (data->cmd_with_path)
		free(data->cmd_with_path);
	exit (g_exit_status);
	return (SUCCESS);
}

static int	get_empty_type(t_list *list)
{
	while (list != NULL && list->type != PIPE)
	{
		if (list->empty == EMPTY || list->empty == NOT_EMPTY)
		{
			return (list->empty);
		}
		list = list->next;
	}
	return (FAILURE);
}

static char	**get_command(t_list *list)
{
	while (list != NULL && list->type != PIPE)
	{
		if (list->type == BUILTIN)
			return (list->data);
		else if (list->type == TOKEN)
			return (list->data);
		list = list->next;
	}
	return (NULL);
}

static	int	finish_by_cmd_not_found(t_exec *data, t_list *list, \
			t_env **lst, int empty)
{
	if (empty != 0)
		g_exit_status = 127;
	clear_cmd_not_found(data);
	close_tab_heredoc(data);
	if (list)
		ft_lstclear(&data->head, free);
	if (lst)
		ft_lstclear_env(lst, free);
	if (data->env)
		free_array(data->env);
	free_struct(data);
	return (g_exit_status);
}
