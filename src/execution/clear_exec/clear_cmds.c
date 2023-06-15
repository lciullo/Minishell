/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:30:03 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/15 10:01:01 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_cmd_not_found(t_exec *data, t_list *list, t_env **lst)
{
	ft_dprintf(2, "%s: command not found\n", data->cmd);
	if (list)
		ft_lstclear(&list, free);
	if (lst)
		ft_lstclear_env(lst, free);
	free_struct(data);
	close_cmd_not_found(data);
}

void	clear_execve_issue(t_exec *data, t_list *list, t_env **lst)
{
	close(data->old_fd[0]);
	close(data->new_fd[1]);
	if (list)
		ft_lstclear(&list, free);
	if (lst)
		ft_lstclear_env(lst, free);
	free_struct(data);
	perror("execve");
}

void	clear_is_executable(t_exec *data, t_list *list, t_env **lst)
{
	if (list)
		ft_lstclear(&list, free);
	if (data->pids)
		free(data->pids);
	if (data->fd_heredoc)
		free(data->fd_heredoc);
	if (data->env_path)
		free_array(data->env_path);
	if (lst)
		ft_lstclear_env(lst, free);
	close_cmd_not_found(data);
}

void	clear_builtin_exec(t_exec *data, t_list *list, t_env **lst)
{
	if (list)
		ft_lstclear(&list, free);
	if (lst)
		ft_lstclear_env(lst, free);
	free_struct(data);
	close_all_fds(data);
	close(data->outfile);
	close(data->infile);
}
