/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:36:12 by cllovio           #+#    #+#             */
/*   Updated: 2023/04/24 12:48:48 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char **token, int type)
{
	t_list	*tab;

	(void)type;
	tab = malloc(sizeof(t_list));
	if (!(tab))
		return (NULL);
	tab -> data = token;
	tab -> type = 0;
	tab -> next = NULL;
	return (tab);
}
