
#include "minishell.h"

static int	sort_to_launch_exec(t_list *list, t_exec *data);
static char	**get_command(t_list *list);

int	launch_exec(t_exec *data, t_list *list, t_env **lst)
{
	int	get_type;

	get_type = sort_to_launch_exec(list, data);
	if (get_type == TOKEN)
		execution_of_token(data, list, lst);
	else if (get_type == BUILTIN)
	{
		g_exit_status = 0;
		loop_for_builtin(get_command(list), data, lst);
		clear_builtin_exec(data, list, lst);
		exit(g_exit_status);
	}
	clear_only_redir(data, list, lst);
	exit(g_exit_status);
}

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
