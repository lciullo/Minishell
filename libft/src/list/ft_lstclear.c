/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:14:34 by cllovio           #+#    #+#             */
/*   Updated: 2023/06/11 15:45:08 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	if (!lst || !del)
		return ;
	while ((*lst))
	{
		temp = *lst;
		*lst = (*lst)->next;
		free_array(temp->data);
		free(temp);
	}
}

void	ft_lstclear_env(t_env **lst, void (*del)(void*))
{
	t_env	*temp;

	if (!lst || !del)
		return ;
	while ((*lst))
	{
		temp = *lst;
		*lst = (*lst)->next;
		if (temp->name)
			free(temp->name);
		if (temp->value)
			free(temp->value);
		if (temp)
			free(temp);
	}
}
