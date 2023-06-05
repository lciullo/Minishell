/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 09:10:18 by cllovio           #+#    #+#             */
/*   Updated: 2023/06/05 10:41:42 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handles_quote(char *line, char *new_line, int *i, int *j);
static void	handles_double_redir(char *line, char *new_line, int *i, int *j);
static void	handles_pipe_and_simple_redir(char *line, char *new_line, \
		int *i, int *j);

char	*add_space(char	*line, t_data *data)
{
	char	*new_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_line = malloc(sizeof(char) * (data->len_line + \
	((data->nbr_pipe * 2 + data->nbr_redir * 2)) + 1));
	if (!new_line)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			handles_quote(line, new_line, &i, &j);
		if (line[i] && ((line[i] == '>' && line[i + 1] == '>') \
		|| (line[i] && line[i] == '<' && line[i + 1] == '<')))
			handles_double_redir(line, new_line, &i, &j);
		else if (line[i] && (line[i] == '|' || (line[i] == '>' && \
		line[i + 1] != '>') || (line[i] == '<' && line[i + 1] != '<')))
			handles_pipe_and_simple_redir(line, new_line, &i, &j);
		else if (line[i])
			new_line[j++] = line[i++];
	}
	new_line[j] = '\0';
	return (new_line);
}

static void	handles_quote(char *line, char *new_line, int *i, int *j)
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
	if (line[*i] && (line[*i] == '\'' || line[*i] == '\"'))
	{
		new_line[*j] = line[*i];
		*i = *i + 1;
		*j = *j + 1;
	}
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
