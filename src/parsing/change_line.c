/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:08:31 by cllovio           #+#    #+#             */
/*   Updated: 2023/06/04 15:10:03 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*change_line(t_data *data)
{
	char	*new_line;

	new_line = add_space(data->line, data);
	if (!new_line)
		return (NULL);
	new_line = expand(new_line, data->lst_env);
	if (!new_line)
		return (NULL);
	replace_space(new_line, data, 0);
	return (new_line);
}

char	*add_space(char	*line, t_data *data)
{
	char	*new_line;

	new_line = malloc(sizeof(char) * (data->len_line + \
	((data->nbr_pipe * 2 + data->nbr_redir * 2)) + 1));
	if (!new_line)
		return (NULL);
	new_line = check_separator(line, new_line, 0, 0);
	return (new_line);
}

//trop de ligne
char	*check_separator(char *line, char*new_line, int i, int j)
{
	char	quote;

	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			quote = line[i];
			new_line[j++] = line[i++];
			while (line[i])
			{
				if (line[i] == quote)
					break ;
				else
					new_line[j++] = line[i++];
			}
		}
		if (line[i] && ((line[i] == '>' && line[i + 1] == '>') \
		|| (line[i] && line[i] == '<' && line[i + 1] == '<')))
		{
			new_line[j++] = ' ';
			new_line[j++] = line[i++];
			new_line[j++] = line[i];
			new_line[j] = ' ';
		}
		else if (line[i] && (line[i] == '|' || (line[i] == '>' && \
		line[i + 1] != '>') || (line[i] == '<' && line[i + 1] != '<')))
		{
			new_line[j++] = ' ';
			new_line[j++] = line[i];
			new_line[j] = ' ';
		}
		else
			new_line[j] = line[i];
		if (line[i])
		{
			j++;
			i++;
		}
	}
	new_line[j] = '\0';
	return (new_line);
}

void	replace_space(char *line, t_data *data, int i)
{
	int		check_quote;
	char	quote;

	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			check_quote = 0;
			quote = line[i++];
			while (line[i++] && check_quote == 0)
			{
				if (line[i] == quote)
				{
					check_quote = 1;
					break ;
				}
				else if (line[i] == ' ')
					line[i] = -1;
				if (line[i] == '\'' || line[i] == '\"')
					data->nbr_quote--;
			}
		}
		if (line[i])
			i++;
	}
}
