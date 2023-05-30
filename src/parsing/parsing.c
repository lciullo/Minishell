/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:41:46 by cllovio           #+#    #+#             */
/*   Updated: 2023/05/30 14:21:04 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	check_error(t_data *data)
{
	if (skip_white_space(data->line) == 1)
		return (1);
	if (check_quote(data->line) == 1)
		return (1);
	if (check_char(data->line) == false)
		return (1);
	if (check_pipe(data->line) == 1)
		return (1);
	if (check_redir(data->line, data) == 1)
		return (1);
	return (0);
}
