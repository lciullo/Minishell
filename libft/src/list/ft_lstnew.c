/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:36:12 by cllovio           #+#    #+#             */
/*   Updated: 2023/05/26 16:05:53 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char **token, int type)
{
	t_list	*tab;

	tab = malloc(sizeof(t_list));
	if (!(tab))
		return (NULL);
	tab->data = token;
	tab->type = type;
	tab->fd = 0;
	tab->next = NULL;
	return (tab);
}

t_env	*ft_lstnew_env(char *name, char *value)
{
	t_env	*data;

	data = malloc(sizeof(t_env));
	if (!(data))
		return (NULL);
	data ->name = name;
	data ->value = value;
	data ->equal = 0;
	data ->next = NULL;
	return (data);
}
