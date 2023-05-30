/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:30:03 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/30 14:51:11 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_dup_issu(t_exec *data, t_list *list, t_env *lst_env)
{
	close(data->new_fd[1]);
	ft_lstclear(&list, free);
	free_array(data->env_path);
	free(data->pids);
	ft_lstclear_env(&lst_env, free);
}

void	clear_cmd_not_found(t_exec *data, t_list *list, t_env *lst_env)
{
	ft_dprintf(2, "%s: command not found\n", data->cmd);
	ft_lstclear(&list, free);
	ft_lstclear_env(&lst_env, free);
	free_struct(data);
	close_cmd_not_found(data);
}

void	clear_files_issu(t_exec *data, t_list *list, t_env *lst_env)
{
	puts("clear infile");
	ft_lstclear(&list, free);
	ft_lstclear_env(&lst_env, free);
	free_struct(data);
}

void	clear_execve_issu(t_exec *data, t_list *list, t_env *lst_env)
{
	close(data->old_fd[0]);
	close(data->new_fd[1]);
	ft_lstclear(&list, free);
	ft_lstclear_env(&lst_env, free);
	free_struct(data);
	perror("execve");
}
