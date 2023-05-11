/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:47:56 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/11 11:49:59 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_print_list(t_list *lst)
{
	int	i;

	i = 0;
	ft_dprintf(1, "IN PRINT LIST\n");
	ft_dprintf(1, "===============================\n");
	while (lst != NULL && lst->type != PIPE)
	{
		i = 0;
		while (lst->data[i] != NULL)
		{
			ft_dprintf(1, "row[%s]\n", lst->data[i]);
			i++;
		}
		lst = lst->next;
	}
	ft_dprintf(1, "===============================\n");
}
