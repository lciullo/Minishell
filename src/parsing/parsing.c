/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:41:46 by cllovio           #+#    #+#             */
/*   Updated: 2023/06/05 10:56:02 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

t_list	*parsing(char *line, t_data *data, t_env **lst_env)
{
	t_list		*list;
	char		*new_line;

	list = NULL;
	data->lst_env = lst_env;
	data->line = line;
	init_structure(data);
	if (check_error(data) == 1)
		return (NULL);
	new_line = change_line(data);
	list = create_list(new_line, data);
	if (!list)
		return (NULL);
	return (list);
}
