/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:36:12 by cllovio           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/06/05 10:30:28 by lciullo          ###   ########.fr       */
=======
/*   Updated: 2023/05/31 08:35:18 by lciullo          ###   ########.fr       */
>>>>>>> 96bc9bc364ecd1355a5ac1e35544a7d01ed3cc12
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
		ft_dprintf(1, "declare -x %s=\"%s\n\"", copy->name, copy->value);
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
