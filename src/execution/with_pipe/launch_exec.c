
#include "minishell.h"

static int	sort_to_launch_exec(t_list *list, t_exec *data)
{
	while (list != NULL && list->type != PIPE)
	{
		if (list->type == BUILTIN)
		{
			data->cmd = list->data[0];
			return (BUILTIN);
		}
		else if (list->type == TOKEN)
		{
			data->cmd = list->data[0];
			return (TOKEN);
		}
		list = list->next;
	}
	return (-1);
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
	return (-1);
}

static int	execution_of_token(t_exec *data, t_list *list, t_env **lst, char **env)
{
	int	empty;

	empty = get_empty_type(list);
	data->cmd_with_path = check_cmd_access(data->env_path, data->cmd, empty);
	if (!data->cmd_with_path)
	{
		if (empty != 0)
			g_exit_status = 127;
		clear_cmd_not_found(data, list, lst);
		close_tab(data);
		if (env)
			free_array(env);
		exit(g_exit_status);
	}
	close_tab(data);
	if (data->cmd_with_path != NULL && is_executable(data->cmd_with_path, data, list, lst) == 0)
	{
		g_exit_status = 1;
		execve(data->cmd_with_path, get_command(list), env);
		clear_execve_issue(data, list, lst);
	}
	if (env)
		free_array(env);
	if (data->cmd_with_path)
		free(data->cmd_with_path);
	exit (g_exit_status);
	return (0);
}

int	launch_exec(t_exec *data, t_list *list, t_env **lst, char **env)
{
	int	get_type;

	get_type = sort_to_launch_exec(list, data);
	if (get_type == TOKEN)
		execution_of_token(data, list, lst, env);
	else if (get_type == BUILTIN)
	{
		g_exit_status = 0;
		loop_for_builtin(get_command(list), data, lst);
		clear_builtin_exec(data, list, lst);
		exit(g_exit_status);
	}
	clear_only_redir(data, list, lst, env);
	exit(g_exit_status);
}
