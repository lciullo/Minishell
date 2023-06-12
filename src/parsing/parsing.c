/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:41:46 by cllovio           #+#    #+#             */
/*   Updated: 2023/06/12 12:59:27 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_nbr_pipe(char *line, t_data *data);

t_list	*parsing(char *line, t_data *data, t_env *lst_env)
{
	t_list		*list;
	char		**tab_line;
	char		*new_line;

	list = NULL;
	init_structure(data, lst_env, line);
	if (check_error(data) == false)
		return (NULL);
	new_line = change_line(data);
	if (!(new_line))
		return (print_error(MALLOC_ERR), NULL);
	get_nbr_pipe(new_line, data);
	tab_line = ft_split_parsing(new_line);
	free(new_line);
	if (!tab_line)
		return (print_error(MALLOC_ERR), NULL);
	tab_line = change_order(tab_line, data);
	if (!(tab_line))
		return (print_error(MALLOC_ERR), NULL);
	change_tab(tab_line, 1);
	list = create_list(data, lst_env, tab_line);
	if (!list)
		return (print_error(MALLOC_ERR), NULL);
	return (list);
}

void	get_nbr_pipe(char *line, t_data *data)
{
	int	i;

	i = 0;
	data->nbr_pipe = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			skip_quote(line, &i, line[i]);
		if (line[i] && line[i] == '|')
			data->nbr_pipe++;
		if (line[i])
			i++;
	}
}

bool	check_error(t_data *data)
{
	if (skip_white_space(data->line) == 1)
		return (false);
	if (check_quote(data->line) == false)
		return (false);
	/* if (check_wrong_character(data->line) == false)
	 	return (false);*/
	if (check_pipe(data->line) == false)
		return (false);
	if (check_redir(data->line, data) == false)
		return (false);
	if (data->nbr_pipe >= 3333)
		return (false);
	return (true);
}
