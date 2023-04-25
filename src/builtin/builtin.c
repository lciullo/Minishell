/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisa <lisa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:07:54 by lciullo           #+#    #+#             */
/*   Updated: 2023/04/25 10:44:50 by lisa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	loop_for_builtin(t_list **lst, t_exec *data)
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
			else if (ft_strcmp(head->data[i], "cd") == 0)
				implement_cd(head->data);
			else if (ft_strcmp(head->data[i], "pwd") == 0)
				implement_pwd(head->data);
			else if (ft_strcmp(head->data[i], "exit") == 0)
				implement_exit(head->data, data);
			i++;
		}
		head = head->next;
	}
}
