/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:02:50 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/02 14:55:48 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_token(t_list *list, t_exec *data)
{
	while (list != NULL && list->type != PIPE)
	{
		if (list->type == TOKEN)
		{
			data->cmd = list->data[0];
			return (1);
		}
		list = list->next;
	}
	return (0);
}

static int	is_builtin_in_block(t_list *list, t_exec *data)
{
	while (list != NULL && list->type != PIPE)
	{
		if (list->type == BUILTIN)
		{
			data->cmd = list->data[0];
			return (1);
		}
		list = list->next;
	}
	return (0);
}

static char	**get_token(t_list *list)
{
	while (list != NULL && list->type != PIPE)
	{
		if (list->type == TOKEN)
			return (list->data);
		list = list->next;
	}
	return (NULL);
}

static char	**get_builtin(t_list *list)
{
	while (list != NULL && list->type != PIPE)
	{
		if (list->type == BUILTIN)
		{
			return (list->data);
		}
		list = list->next;
	}
	return (NULL);
}

static int	execution_of_token(t_exec *data, t_list *list, t_env *lst, char **env)
{
	data->cmd_with_path = check_cmd_acess(data->env_path, data->cmd);
	if (!data->cmd_with_path)
	{
		clear_cmd_not_found(data, list, lst);
		close_tab(data);
		exit(1);
	}
	close_tab(data);
	if (data->cmd_with_path != NULL && is_executable(data->cmd_with_path) == 0)
	{
		execve(data->cmd_with_path, get_token(list), env);
		clear_execve_issue(data, list, lst);
	}
	return (0);
}

int	launch_exec(t_exec *data, t_list *list, t_env *lst, char **env)
{

	if (is_token(list, data) == 1)
	{
		execution_of_token(data, list, lst, env);
	}
	else if (is_builtin_in_block(list, data) == 1)
	{
		loop_for_builtin(get_builtin(list), data, lst);
		ft_lstclear(&list, free);
		ft_lstclear_env(&lst, free);
		free_struct(data);
		close_all_fds(data);
		close(data->outfile);
		close(data->infile);
		exit(1);
	}
	close(data->outfile);
	exit(1);
	return (0);
}
