
#include "minishell.h"

static int	get_nb_total_of_cmd(t_list *list)
{
	int	nb_cmd;

	nb_cmd = 0;
	while (list != NULL)
	{
		if (list->type == BUILTIN || list->type == TOKEN)
			nb_cmd++;
		list = list->next;
	}
	return (nb_cmd);
}

static	int	get_nb_builtin(t_list *list)
{
	int	nb_builtin;

	nb_builtin = 0;
	while (list != NULL)
	{
		if (list->type == BUILTIN)
			nb_builtin++;
		list = list->next;
	}
	return (nb_builtin);
}

void	free_struct(t_exec *data)
{
	if (data->env_path)
		free_array(data->env_path);
	if (data->cmd_with_path)
		free(data->cmd_with_path);
	if (data->pids)
		free(data->pids);
	if (data->fd_heredoc)
		free(data->fd_heredoc);
}

static	int	initialize_integers(t_list *list, t_exec *data, t_data *parsing)
{
	data->exec_progress = 0;
	data->nb_pids = 0;
	data->infile = 0;
	data->outfile = 0;
	data->expand = 0;
	data->old_fd[0] = 0;
	data->old_fd[1] = 0;
	data->new_fd[0] = 0;
	data->new_fd[1] = 0;
	data->tmp_fd_heredoc[0] = 0;
	data->tmp_fd_heredoc[1] = 0;
	data->in_dir = 0;
	data->out_dir = 0;
	data->nb_block = parsing->nbr_pipe + 1;
	data->nb_cmd = get_nb_total_of_cmd(list);
	data->nb_builtin = get_nb_builtin(list);
	data->nb_heredoc = parsing->nbr_here_doc;
	data->nb_args = data->nb_cmd + parsing->nbr_redir;
	data->pids = ft_calloc(data->nb_block, sizeof(pid_t));
	if (!data->pids)
		return (-1);
	data->fd_heredoc = ft_calloc(data->nb_heredoc, sizeof(int));
	if (!data->fd_heredoc)
	{
		free(data->pids);
		return (-1);
	}
	return (0);
}

int	init_struct(t_list *list, t_env *lst, t_exec *data, t_data *parsing)
{
	if (initialize_integers(list, data, parsing) == -1)
		return (-1);
	data->cmd_with_path = NULL;
	data->cmd = NULL;
	data->paths = NULL;
	data->env_path = NULL;
	data->head = list;
	if (!lst)
		data->env = NULL;
	else
	{
		data->env = fill_env(lst);
		if (!data->env)
			return (0);
	}
	return (0);
}
