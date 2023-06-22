#include "minishell.h"

void	clear_cmd_not_found(t_exec *data, t_list *list, t_env **lst)
{
	ft_dprintf(2, "%s: command not found\n", data->cmd);
	close_cmd_not_found(data);
	if (list)
		ft_lstclear(&data->head, free);
	if (lst)
		ft_lstclear_env(lst, free);
	free_struct(data);
}

void	clear_only_redir(t_exec *data, t_list *list, t_env **lst)
{
	close(data->outfile);
	if (list)
		ft_lstclear(&data->head, free);
	if (lst)
		ft_lstclear_env(lst, free);
	if (data->env)
		free_array(data->env);
	free_struct(data);
}

void	clear_execve_issue(t_exec *data, t_list *list, t_env **lst)
{
	close(data->old_fd[0]);
	close(data->new_fd[1]);
	if (list)
		ft_lstclear(&data->head, free);
	if (lst)
		ft_lstclear_env(lst, free);
	free_struct(data);
	perror("execve");
}

void	clear_is_executable(t_exec *data, t_list *list, t_env **lst)
{
	close_cmd_not_found(data);
	if (list)
		ft_lstclear(&data->head, free);
	if (data->pids)
		free(data->pids);
	if (data->fd_heredoc)
		free(data->fd_heredoc);
	if (data->env_path)
		free_array(data->env_path);
	if (lst)
		ft_lstclear_env(lst, free);
}

void	clear_builtin_exec(t_exec *data, t_list *list, t_env **lst)
{
	close_all_fds(data);
	close(data->outfile);
	close(data->infile);
	if (list)
		ft_lstclear(&data->head, free);
	if (lst)
		ft_lstclear_env(lst, free);
	free_struct(data);
	if (data->env != NULL)
		free_array(data->env);
}
