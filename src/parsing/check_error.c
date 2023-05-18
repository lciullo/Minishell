/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:59:20 by cllovio           #+#    #+#             */
/*   Updated: 2023/05/18 16:18:16 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_error(char *line, t_data *data)
{
	if (skip_white_space(line) == 1)
	 	return (1);
	if ((line[0] == ':' && line[skip_white_space_2(line, 1)] == '\0') || (line[0] == '!' && line[skip_white_space_2(line, 1)] == '\0') )
		return (1);
	if (check_quote(line) == 1)
		return (1);
	if (check_pipe(line) == 1)
		return (1);
	if (check_redir(line, data) == 1)
		return (1);
	return (0);
}

int	check_quote(char *line)
{
	int		i;
	char	quote;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			quote = line[i];
			if (nbr_quote(line, &i, quote) == 1)
				return (ft_dprintf(2, "syntax error\n"), 1);
		}
		else if (line[i] != '\0')
			i++;
	}
	return (0);
}

int	nbr_quote(char *line, int *i, char quote)
{
	int	quote_nbr;

	quote_nbr = 0;
	while (line[*i])
	{
		if (quote == '\"' && line[*i] == '\\' && line[*i + 1] != '\'')
			*i = *i + 2;
		else if (line[*i] == quote)
		{
			quote_nbr++;
			*i = *i + 1;
		}
		else
			*i = *i + 1;
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
		}
		else
			i++;
	}
	data->len_line = i;
	data->nbr_redir = data->nbr_here_doc + \
	data->nbr_output + data->nbr_append + data->nbr_input;
	return (0);
}
