/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:07:54 by lciullo           #+#    #+#             */
/*   Updated: 2023/04/24 14:39:02 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	loop_for_builtin(t_list **lst)
{
	int		i;
	t_list	*head;

	i = 0;
	head = *lst;
	while (head != NULL)
	{
		while (head->data[i] != NULL)
		{
			if (ft_strcmp(head->data[i], "echo") == 0)
				implement_echo(head->data);
			i++;
		}
		head = head->next;
	}
}
