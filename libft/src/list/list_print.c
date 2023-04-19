/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:36:12 by cllovio           #+#    #+#             */
/*   Updated: 2023/04/19 08:58:03 by lciullo          ###   ########.fr       */
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
