/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:07:54 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/02 15:10:14 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	loop_for_builtin(t_list **lst, t_exec *data, char **env)
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
			else if (ft_strcmp(head->data[i], "env") == 0)
				implement_env(env);
			i++;
		}
		head = head->next;
	}
}


int	is_builtin(t_list **lst)
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
				return (1);
			else if (ft_strcmp(head->data[i], "cd") == 0)
				return (1);
			else if (ft_strcmp(head->data[i], "pwd") == 0)
				return (1);
			else if (ft_strcmp(head->data[i], "exit") == 0)
				return (1);
			else if (ft_strcmp(head->data[i], "env") == 0)
				return (1);
			i++;
		}
		head = head->next;
	}
	return (0);
}
