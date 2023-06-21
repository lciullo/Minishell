/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisa <lisa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 10:12:14 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/21 19:34:35 by lisa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_exec_files_issue(t_list *list, t_env **lst, t_exec *data)
{
	close_all_fds(data);
	close_tab_heredoc(data);
	free_struct(data);
	if (list)
		ft_lstclear(&list, free);
	if (lst)
		ft_lstclear_env(lst, free);
	if (data->env)
		free_array(data->env);
}

void	clear_one_builtin_exec_files(t_exec *data)
{
	close_all_fds(data);
	close_tab_heredoc(data);
	free_struct(data);
	if (data->env)
		free_array(data->env);
}

void	clear_dup_issue(t_exec *data, t_list *list, t_env **lst)
{
	close(data->new_fd[1]);
	if (list)
		ft_lstclear(&data->head, free);
	if (data->env)
		free_array(data->env);
	free_struct(data);
	if (lst)
		ft_lstclear_env(lst, free);
}

void	clear_dup_issue_builtin(t_exec *data, t_list *list, t_env **lst)
{
	if (list)
		ft_lstclear(&data->head, free);
	if (data->env)
		free_array(data->env);
	free_struct(data);
	if (lst)
		ft_lstclear_env(lst, free);
	ft_close(data->infile);
	ft_close(data->outfile);
}

void	clear_heredoc_main_process(t_exec *data)
{
	ft_close(data->infile);
	free_struct(data);
	if (data->env != NULL)
		free_array(data->env);
}