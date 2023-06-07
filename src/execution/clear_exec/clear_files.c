/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 10:12:14 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/06 16:50:47 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_exec_files_issu(t_list *list, t_env **lst, t_exec *data)
{
	close_all_fds(data);
	close_tab(data);
	free_struct(data);
	if (list)
		ft_lstclear(&list, free);
	if (lst)
		ft_lstclear_env(lst, free);
}

void	clear_dup_issue(t_exec *data, t_list *list, t_env **lst)
{
	close(data->new_fd[1]);
	if (list)
		ft_lstclear(&list, free);
	if (data->env_path)
		free_array(data->env_path);
	if (data->pids)
		free(data->pids);
	if (lst)
		ft_lstclear_env(lst, free);
}
