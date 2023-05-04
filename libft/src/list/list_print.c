/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:36:12 by cllovio           #+#    #+#             */
/*   Updated: 2023/05/04 15:55:01 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


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
