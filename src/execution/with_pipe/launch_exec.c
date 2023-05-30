/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:02:50 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/30 14:46:05 by lciullo          ###   ########.fr       */
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

static int	execution_of_token(t_exec *data, t_list *list, t_env *lst_env, char **env)
{
	data->cmd_with_path = check_cmd_acess(data->env_path, data->cmd);
	if (!data->cmd_with_path)
	{
		clear_cmd_not_found(data, list, lst_env);
		exit(1);
	}
	execve(data->cmd_with_path, get_token(list), env);
	clear_execve_issu(data, list, lst_env);
	return (0);
}

int	launch_exec(t_exec *data, t_list *list, t_env *lst_env, char **env)
{

	if (is_token(list, data) == 1)
		execution_of_token(data, list, lst_env, env);
	return (0);
}
