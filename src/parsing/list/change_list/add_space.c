/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 09:10:18 by cllovio           #+#    #+#             */
/*   Updated: 2023/06/23 14:20:50 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handles_quote(char *line, char *new_line, int *i, int *j);
static void	handles_double_redir(char *line, char *new_line, int *i, int *j);
static void	handles_pipe_and_simple_redir(char *line, char *new_line, \
		int *i, int *j);

char	*add_space(char	*line, int status, int malloc_size)
{
	char	*new_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_line = calloc(malloc_size, sizeof(char));
	if (!new_line)
		return (NULL);
	while (line[i])
	{
		status = 0;
		if (line[i] == '\'' || line[i] == '\"')
			status = handles_quote(line, new_line, &i, &j);
		if (line[i] && ((line[i] == '>' && line[i + 1] == '>') \
		|| (line[i] && line[i] == '<' && line[i + 1] == '<')))
			handles_double_redir(line, new_line, &i, &j);
		else if (line[i] && (line[i] == '|' || (line[i] == '>' && \
		line[i + 1] != '>') || (line[i] == '<' && line[i + 1] != '<')))
			handles_pipe_and_simple_redir(line, new_line, &i, &j);
		else if (line[i] && status != 1)
			new_line[j++] = line[i++];
	}
	new_line[j] = '\0';
	return (new_line);
}

static int	handles_quote(char *line, char *new_line, int *i, int *j)
{
	char	quote;

	quote = line[*i];
	new_line[*j] = line[*i];
	*i = *i + 1;
	*j = *j + 1;
	while (line[*i])
	{
		if (line[*i] == quote)
			break ;
		else
		{
			new_line[*j] = line[*i];
			*j = *j + 1;
			*i = *i + 1;
		}
	}
	if (line[*i] && (line[*i] == quote))
	{
		new_line[*j] = line[*i];
		*i = *i + 1;
		*j = *j + 1;
	}
	return (1);
}

static void	handles_double_redir(char *line, char *new_line, int *i, int *j)
{
	new_line[*j] = ' ';
	*j = *j + 1;
	new_line[*j] = line[*i];
	*j = *j + 1;
	*i = *i + 1;
	new_line[*j] = line[*i];
	*j = *j + 1;
	new_line[*j] = ' ';
	if (line[*i])
	{
		*j = *j + 1;
		*i = *i + 1;
	}
}

static void	handles_pipe_and_simple_redir(char *line, char *new_line, \
		int *i, int *j)
{
	new_line[*j] = ' ';
	*j = *j + 1;
	new_line[*j] = line[*i];
	*j = *j + 1;
	new_line[*j] = ' ';
	if (line[*i])
	{
		*j = *j + 1;
		*i = *i + 1;
	}
}

//'$USER'""'''|$USER'|"$USER"