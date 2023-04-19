/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:36:12 by cllovio           #+#    #+#             */
/*   Updated: 2023/04/19 08:40:50 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char **cmd, int type)
{
	t_list	*tab;

	(void)type;
	tab = malloc(sizeof(t_list));
	if (!(tab))
		return (NULL);
	tab -> data = cmd;
	tab -> type = 0;
	tab -> next = NULL;
	return (tab);
}
