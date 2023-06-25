/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:12:09 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/25 16:12:12 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_cmd_not_found(t_exec *data)
{
	char	*str;

	str = NULL;
	close_cmd_not_found(data);
	str = ft_strjoin(data->cmd, " : command not found\n");
	if (!str)
	{
		perror("Malloc failed in command not found ft_strjoin");
		return ;
	}
	write(2, str, ft_strlen(str));
	free(str);
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
