/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:04:05 by cllovio           #+#    #+#             */
/*   Updated: 2023/06/22 11:16:00 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_structure(t_data *data, t_env *lst_env, char *line)
{
	data->nbr_pipe = 0;
	data->nbr_quote = 0;
	data->nbr_here_doc = 0;
	data->nbr_append = 0;
	data->len_line = 0;
	data->nbr_infile = 0;
	data->nbr_outfile = 0;
	data->nbr_redir = 0;
	data->start = 0;
	data->end = 0;
	data->lst_env = lst_env;
	data->line = line;
}

bool	is_builtins(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (true);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (true);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (true);
	else if (ft_strcmp(cmd, "export") == 0)
		return (true);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (true);
	else if (ft_strcmp(cmd, "env") == 0)
		return (true);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (true);
	return (false);
}

bool	is_white_space(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (true);
	return (false);
}

bool	if_check(int type, char *line, int i)
{
	if (type == 0 && (line[i] == '$' && (ft_isalnum(line[i + 1]) == true || \
	line[i + 1] == '_' || line[i + 1] == '?' || line[i + 1] == '\'' \
	|| line[i + 1] == '\"' || line[i + 1] == '$')))
		return (true);
	if (type == 1 && (line[i] == '$' && (ft_isalnum(line[i + 1]) == true \
	|| line[i + 1] == '_' || line[i + 1] == '?' || line[i + 1] == '$')))
		return (true);
	if (type == 2 && (is_white_space(line[i]) == true && \
	((line[skip_ws_i(line, i + 1)] == '\0' || \
	line[skip_ws_i(line, i + 1)] == '<' || \
	line[skip_ws_i(line, i + 1)] == '>' \
	|| line[skip_ws_i(line, i + 1)] == '|'))))
		return (true);
	return (false);
}