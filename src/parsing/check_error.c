/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:59:20 by cllovio           #+#    #+#             */
/*   Updated: 2023/06/04 12:44:36 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_wrong_character(char *line, t_data *data);

//ajouter un check de tout les caractere qui ne sont pas a gerer 
//pour mettre un syntax error [{()}]\\;&^%#@*,:
bool	check_error(t_data *data)
{
	if (skip_white_space(data->line) == 1)
		return (false);
	if (check_quote(data->line) == false)
		return (false);
	if (check_wrong_character(data->line, data) == false)
	 	return (false);
	if (check_pipe(data->line) == false)
		return (false);
	if (check_redir(data->line, data) == false)
		return (false);
	return (true);
}


bool	check_wrong_character(char *line, t_data *data)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			skip_quote(line, &i, line[i]);
		if (line[i] && (line[i] == '[' || line[i] == '{' || line[i] == '(' \
		|| line[i] == ')' || line[i] == '}' || line[i] == ']' || \
		line[i] == '\\' || line[i] == ';' || line[i] == '&' || line[i] == '^' \
		|| line[i] == '%' || line[i] == '#' || line[i] == '@' || line[i] == '*' \
		|| line[i] == ',' || line[i] == ':'))
			return (ft_dprintf(2, "on doit pas gerer ca grand fou\n"), false);
		if (line[i])
			i++;
	}
	data->len_line = i;
	return (true);
}

bool	check_quote(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (nbr_quote(line, &i, line[i]) == 1)
				return (ft_dprintf(2, "syntax error\n"), false);
		}
		if (line[i] != '\0')
			i++;
	}
	return (true);
}

int	nbr_quote(char *line, int *i, char quote)
{
	int	quote_nbr;

	quote_nbr = 1;
	*i = *i + 1;
	while (line[*i])
	{
		if (line[*i] != quote)
			*i = *i + 1;
		else if (line[*i] == quote)
		{
			quote_nbr ++;
			break ;
		}
	}
	return (quote_nbr % 2);
}

bool	check_pipe(char	*line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (i == 0 && line[i] == '|')
			return (ft_dprintf(2, "syntax error\n"), false);
		if (line[i] == '|' && (line[skip_white_space_2(line, i + 1)] == '\0' \
		|| line[skip_white_space_2(line, i + 1)] == '|'))
			return (ft_dprintf(2, "syntax error\n"), false);
		i++;
	}
	return (true);
}

bool	check_redir(char *line, t_data *data)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			skip_quote(line, &i, line[i]);
		if (line[i] && line[i] == '|')
			data->nbr_pipe++;
		if (line[i] && (line[i] == '<' || line[i] == '>'))
		{
			if (skip_redir(line, &i, line[i], data) > 2)
				return (ft_dprintf(2, "syntax error\n"), false);
			if (line[skip_white_space_2(line, i + 1)] == '\0')
				return (ft_dprintf(2, "syntax error\n"), false);
		}
		else if (line[i])
			i++;
	}
	data->nbr_redir = data->nbr_here_doc + \
	data->nbr_outfile + data->nbr_append + data->nbr_infile;
	return (true);
}
