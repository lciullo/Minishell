/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:59:20 by cllovio           #+#    #+#             */
/*   Updated: 2023/05/30 14:19:29 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_char(char *line)
{
	int	i;

	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			skip_quote(line, &i, line[i]);
		if (line[i] == '!' || line[i] == '[' || line[i] == '{' \
		|| line[i] == '(' || line[i] == ')' || line[i] == '}' \
		|| line[i] == ']' || line[i] == '\\' || line[i] == ';' \
		|| line[i] == '&' || line[i] == '^' || line[i] == '%' \
		|| line[i] == '#' || line[i] == '@' || line[i] == '*')
			return (false);
		i++;
	}
	return (true);
}

int	check_quote(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (nbr_quote(line, &i, line[i]) == 1)
				return (ft_dprintf(2, "syntax error\n"), 1);
		}
		if (line[i] != '\0')
			i++;
	}
	return (0);
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

int	check_pipe(char	*line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (i == 0 && line[i] == '|')
			return (ft_dprintf(2, "syntax error\n"), 1);
		if (line[i] == '|' && (line[skip_white_space_2(line, i + 1)] == '\0' \
		|| line[skip_white_space_2(line, i + 1)] == '|'))
			return (ft_dprintf(2, "syntax error\n"), 1);
		i++;
	}
	return (0);
}

int	check_redir(char *line, t_data *data)
{
	int	i;

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
				return (ft_dprintf(2, "syntax error\n"), 1);
			if (line[skip_white_space_2(line, i + 1)] == '\0')
				return (ft_dprintf(2, "syntax error\n"), 1);
		}
		else
			i++;
	}
	data->len_line = i;
	data->nbr_redir = data->nbr_here_doc + \
	data->nbr_outfile + data->nbr_append + data->nbr_infile;
	return (0);
}
