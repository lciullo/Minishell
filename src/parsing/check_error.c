/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 14:39:39 by cllovio           #+#    #+#             */
/*   Updated: 2023/06/25 14:39:41 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_quote(char *line);
static int	nbr_quote(char *line, int *i, char quote);
static bool	check_pipe(char	*line);
static bool	check_redir(char *line, t_data *data);

bool	check_error(t_data *data)
{
	if (check_quote(data->line) == false)
		return (false);
	if (check_pipe(data->line) == false)
		return (false);
	if (check_redir(data->line, data) == false)
		return (false);
	if (data->nbr_pipe >= 3333)
		return (false);
	return (true);
}

static bool	check_quote(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (nbr_quote(line, &i, line[i]) == 1)
			{
				print_error(QUOTE_ERR);
				return (false);
			}
		}
		if (line[i] != '\0')
			i++;
	}
	return (true);
}

static int	nbr_quote(char *line, int *i, char quote)
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

static bool	check_pipe(char	*line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (i == 0 && line[i] == '|')
			return (print_error(PIPE_ERR), false);
		if (line[i] == '\'' || line[i] == '\"')
			skip_quote(line, &i, line[i]);
		if (line[i] == '|' && (line[skip_ws_i(line, i + 1)] == '\0' \
		|| line[skip_ws_i(line, i + 1)] == '|'))
			return (print_error(PIPE_ERR), false);
		i++;
	}
	return (true);
}

static bool	check_redir(char *line, t_data *data)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			skip_quote(line, &i, line[i]);
		if (line[i] == '|')
			data->nbr_pipe++;
		if (line[i] && (line[i] == '<' || line[i] == '>'))
		{
			if (skip_redir(line, &i, line[i], data) > 2)
				return (print_error(REDIR_ERR), false);
			if (if_check(2, line, i) == true || ((line[i] == '\0' || \
			line[i] == '<' || line[i] == '>' || line[i] == '|')))
				return (print_error(REDIR_ERR), false);
		}
		else
			i++;
	}
	data->len_line = i;
	data->nbr_redir = data->nbr_here_doc + \
	data->nbr_outfile + data->nbr_append + data->nbr_infile;
	return (true);
}
