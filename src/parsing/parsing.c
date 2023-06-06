/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:41:46 by cllovio           #+#    #+#             */
/*   Updated: 2023/06/06 09:53:26 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*parsing(char *line, t_data *data, t_env **lst_env)
{
	t_list		*list;
	char		**tab_line;
	char		*new_line;

	list = NULL;
	init_structure(data, lst_env, line);
	if (check_error(data) == false)
		return (NULL);
	new_line = change_line(data);
	tab_line = ft_split_parsing(new_line);
	free(new_line);
	if (!tab_line)
		return (NULL);
	tab_line = change_order(tab_line, data);
	change_tab(tab_line);
	list = create_list(data, tab_line);
	if (!list)
		return (NULL);
	return (list);
}

bool	check_error(t_data *data)
{
	if (skip_white_space(data->line) == 1)
		return (false);
	if (check_quote(data->line) == false)
		return (false);
	if (check_wrong_character(data->line) == false)
		return (false);
	if (check_pipe(data->line) == false)
		return (false);
	if (check_redir(data->line, data) == false)
		return (false);
	if (data->nbr_pipe >= 3333)
		return (false);
	return (true);
}
