/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:08:31 by cllovio           #+#    #+#             */
/*   Updated: 2023/05/29 18:52:32 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*change_line(t_data *data)
{
	char	*new_line;

	new_line = expand(data->line, data->lst_env);
	if (!new_line)
		return (NULL);
	return (new_line);
}
