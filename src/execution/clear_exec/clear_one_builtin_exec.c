/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_one_builtin_exec.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:16:10 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/25 19:05:20 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_in_child(t_exec *data, t_env **lst, t_list *list)
{
	ft_close(data->infile);
	ft_close(data->outfile);
	close_tab_heredoc(data);
	if (list)
		ft_lstclear(&data->head, free);
	if (lst)
		ft_lstclear_env(lst, free);
	free_struct(data);
	if (data->env)
		free_array(data->env);
}
