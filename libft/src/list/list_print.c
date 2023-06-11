/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:46:00 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/11 11:36:43 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


void	list_print_env(t_env *lst)
{
	t_env	*copy;

	copy = lst;
	while (copy)
	{
		ft_dprintf(1, "%s=%s\n", copy->name, copy->value);
		copy = copy->next;
	}
}

void	list_print_export(t_env *lst)
{
	t_env	*copy;

	copy = lst;
	while (copy)
	{
		if (copy->equal == TRUE)
		{
			if (copy->value)
				ft_dprintf(1, "declare -x %s=\"%s\"\n", copy->name, copy->value);
			else if (!copy->value)
				ft_dprintf(1, "declare -x %s=\"\"\n", copy->name);
		}
		else
		{
			if (copy->name)
				ft_dprintf(1, "declare -x %s\n", copy->name);
		}
		copy = copy->next;
	}
}

void	print_utile_pipe(t_list *lst, int index)
{
	int	i;
	int	pipe;

	i = 0;
	pipe = 0;
	ft_dprintf(1, "IN PRINT UTILE PIPE\n");
	ft_dprintf(1, "===============================\n");
	while (lst != NULL && pipe < index)
	{
		i = 0;
		while (lst->data[i] != NULL)
		{
			ft_dprintf(1, "row[%s]\n", lst->data[i]);
			i++;
		}
		pipe++;
		lst = lst->next;
	}
	ft_dprintf(1, "===============================\n");
}

void	in_exec_print_list(t_list *lst)
{
	int	i;

	i = 0;
	ft_dprintf(1, "IN PRINT LIST\n");
	ft_dprintf(1, "===============================\n");
	while (lst != NULL)
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
