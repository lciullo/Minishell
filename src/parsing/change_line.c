/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:08:31 by cllovio           #+#    #+#             */
/*   Updated: 2023/05/31 08:35:18 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*change_line(t_data *data)
{
	char	*new_line;

	new_line = expand(data->line, data->lst);
	if (!new_line)
		return (NULL);
	return (new_line);
}
