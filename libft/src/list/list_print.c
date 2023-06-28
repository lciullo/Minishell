/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:46:00 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/25 16:24:37 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	list_print_env(t_env *lst)
{
	t_env	*copy;

	copy = lst;
	while (copy)
	{
		if (copy->equal == TRUE)
		{
			if (copy->value)
				ft_dprintf(1, "%s=%s\n", copy->name, copy->value);
			else if (!copy->value)
				ft_dprintf(1, "%s=\"\"\n", copy->name);
		}
		copy = copy->next;
	}
}

void	list_print_export(t_env *lst)
{
	t_env	*copy;

	copy = lst;
	while (copy)
	{
		if (copy->equal == TRUE)
		{
			if (copy->value)
				ft_dprintf(1, "declare -x %s=\"%s\"\n", copy->name, copy->value);
			else if (!copy->value)
				ft_dprintf(1, "declare -x %s=\"\"\n", copy->name);
		}
		else
		{
			if (copy->name)
				ft_dprintf(1, "declare -x %s\n", copy->name);
		}
		copy = copy->next;
	}
}
