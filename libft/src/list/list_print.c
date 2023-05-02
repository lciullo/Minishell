/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:36:12 by cllovio           #+#    #+#             */
/*   Updated: 2023/05/02 13:11:33 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	list_print(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		while (lst->data[i] != NULL)
		{
			ft_dprintf(1, "%s\n", lst->data[i]);
			i++;
		}
		ft_dprintf(1, "%d\n", lst->type);
		lst = lst->next;
	}
	ft_dprintf(1, "\n");
}


void	list_print_env(t_lst_env *lst_env)
{
	t_lst_env	*copy;

	copy = lst_env;
	while (copy)
	{
		ft_dprintf(1, "%s=%s\n", copy->variable, copy->value);
		copy = copy->next;
	}
}
