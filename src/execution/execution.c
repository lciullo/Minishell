
#include "minishell.h"

static int	sort_cmd(t_list *list, t_data *parsing, t_exec *data, t_env **lst);

static	int	launch_heredoc(t_list *list, t_data *parsing, \
				t_exec *data, t_env **lst);

int	execution(t_list *list, t_data *parsing, t_exec *data, t_env **lst)
{
	int	heredoc_check;

	heredoc_check = 0;
	if (init_struct(list, *lst, data, parsing) == FAILURE)
	{
		perror("Malloc failed in structure initialisation");
		return (FAILURE);
	}
	if (parsing->nbr_here_doc >= 1)
	{
		heredoc_check = launch_heredoc(list, parsing, data, lst);
		if (heredoc_check == FAILURE)
			return (FAILURE);
		else if (heredoc_check == ONLY_HEREDOC)
			return (SUCCESS);
	}
	if (sort_cmd(list, parsing, data, lst) == FAILURE)
		return (FAILURE);
	//close_for_heredoc(list);
	ft_close(data->infile);
	free_struct(data);
	if (data->env != NULL)
		free_array(data->env);
	return (SUCCESS);
}

static	int	launch_heredoc(t_list *list, t_data *parsing, \
				t_exec *data, t_env **lst)
{
	int	check;

	check = 0;
	check = loop_for_heredoc(list, data, parsing, lst);
	if (check == FAILURE)
		return (FAILURE);
	if (check == FAILURE || check == 130 || check == 131)
	{
		//close_for_heredoc(list);
		ft_close(data->infile);
		free_struct(data);
		if (data->env != NULL)
			free_array(data->env);
		return (FAILURE);
	}
	if (parsing->nbr_here_doc == data->nb_args)
	{
		//close_for_heredoc(list);
		ft_close(data->infile);
		free_struct(data);
		if (data->env != NULL)
			free_array(data->env);
		return (ONLY_HEREDOC);
	}
	return (SUCCESS);
}

static int	sort_cmd(t_list *list, t_data *parsing, t_exec *data, t_env **lst)
{
	if (data->nb_block == 1 && parsing->nbr_pipe == 0 && data->nb_builtin == 1)
	{
		if (loop_for_infile(list, data) == FAILURE)
			return (FAILURE);
		if (loop_for_outfile(list, data) == FAILURE)
			return (FAILURE);
		get_builtin_and_exec(list, data, lst);
		return (SUCCESS);
	}
	else if (data->nb_block >= 1)
	{
		if (get_path_env(data) == FAILURE)
			return (FAILURE);
		if (loop_pipe_by_pipe(list, data, lst) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
