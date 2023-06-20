
#include "minishell.h"

static int	sort_cmd(t_list *list, t_data *parsing, t_exec *data, t_env **lst)
{
	if (data->nb_block == 1 && parsing->nbr_pipe == 0 && data->nb_builtin == 1)
	{
		if (loop_for_infile(list, data) == -1)
			return (-1);
		if (loop_for_outfile(list, data) == -1)
			return (-1);
		get_builtin_and_exec(list, data, lst);
		return (0);
	}
	else if (data->nb_block >= 1)
	{
		if (get_path_env(data) == -1)
			return (-1);
		if (loop_pipe_by_pipe(list, data, lst) == -1)
			return (-1);
	}
	return (0);
}

int	execution(t_list *list, t_data *parsing, t_exec *data, t_env **lst)
{
	int	check;

	check = 0;
	if (init_struct(list, *lst, data, parsing) == -1)
	{
		perror("Malloc failed in structure initialisation");
		return (-1);
	}
	if (parsing->nbr_here_doc >= 1)
	{
		check = loop_for_heredoc(list, data, lst);
		if (check == -1 || check == 130 || check == 131)
		{
			close_for_heredoc(list);
			ft_close(data->infile);
			free_struct(data);
			if (data->env != NULL)
				free_array(data->env);
			return (-1);
		}
		if (parsing->nbr_here_doc == data->nb_args)
		{
			close_for_heredoc(list);
			ft_close(data->infile);
			free_struct(data);
			if (data->env != NULL)
				free_array(data->env);
			return (0);
		}
	}
	if (sort_cmd(list, parsing, data, lst) == -1)
		return (-1);
	close_for_heredoc(list);
	ft_close(data->infile);
	free_struct(data);
	if (data->env != NULL)
		free_array(data->env);
	return (0);
}
