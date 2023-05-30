/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:14:34 by cllovio           #+#    #+#             */
/*   Updated: 2023/05/30 10:55:59 by lciullo          ###   ########.fr       */
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

void	ft_lstclear_env(t_env **lst_env, void (*del)(void*))
{
	t_env	*temp;

	if (!lst_env || !del)
		return ;
	while ((*lst_env))
	{
		temp = *lst_env;
		*lst_env = (*lst_env)->next;
		free(temp->name);
		free(temp->value);
		free(temp);
	}
}
