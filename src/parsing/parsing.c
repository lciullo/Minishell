/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:41:46 by cllovio           #+#    #+#             */
/*   Updated: 2023/05/31 08:35:18 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*parsing(char *line, t_data *data, t_env **lst)
{
	t_list		*list;
	char		*new_line;

	list = NULL;
	data->lst = lst;
	data->line = line;
	init_structure(data);
	if (check_error(data) == false)
		return (NULL);
	new_line = change_line(data);
	list = create_list(new_line, data);
	if (!list)
		return (NULL);
	return (list);
}
