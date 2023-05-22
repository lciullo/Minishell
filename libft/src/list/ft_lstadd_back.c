/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:10:29 by cllovio           #+#    #+#             */
/*   Updated: 2023/05/22 13:01:21 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (new)
	{
		if (!(*lst))
		{
			*lst = new;
			return ;
		}
		last = ft_lstlast(*lst);
		last->next = new;
	}
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*last;

	if (new)
	{
		if (!(*lst))
		{
			*lst = new;
			return ;
		}
		last = ft_lstlast_env(*lst);
		last->next = new;
	}
}
