
#include "minishell.h"

static int	sort_cmd(t_list *list, t_data *parsing, t_exec *data, t_env **lst);
static	int	launch_heredoc(t_list *list, t_data *parsing, \
				t_exec *data, t_env **lst);
static int 	check_files_one_builtin_exec(t_list *list, t_exec *data);
static	void	clear_after_execution(t_exec *data);

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
	clear_after_execution(data);
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
		clear_heredoc_main_process(data);
		return (FAILURE);
	}
	if (parsing->nbr_here_doc == data->nb_args)
	{
		clear_heredoc_main_process(data);
		return (ONLY_HEREDOC);
	}
	return (SUCCESS);
}

static int	sort_cmd(t_list *list, t_data *parsing, t_exec *data, t_env **lst)
{
	if (data->nb_block == 1 && parsing->nbr_pipe == 0 && data->nb_builtin == 1)
	{
		if (check_files_one_builtin_exec(list, data) == FAILURE)
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

static int check_files_one_builtin_exec(t_list *list, t_exec *data)
{
	if (loop_for_infile(list, data) == FAILURE)
	{
		clear_one_builtin_exec_files(data);
		return (FAILURE);
	}
	if (loop_for_outfile(list, data) == FAILURE)
	{
		clear_one_builtin_exec_files(data);
		return (FAILURE);
	}
	return (SUCCESS);
}

static	void	clear_after_execution(t_exec *data)
{
	ft_close(data->infile);
	free_struct(data);
	if (data->env != NULL)
		free_array(data->env);
}