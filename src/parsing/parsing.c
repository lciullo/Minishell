/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:41:46 by cllovio           #+#    #+#             */
/*   Updated: 2023/05/26 16:09:28 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*parsing(char *line, t_data *data, t_env **lst_env)
{
	t_list		*list;
	char		*new_line;

	list = NULL;
	init_structure(data);
	if (check_error(line, data) == 1)
		return (NULL);
	new_line = add_space(line, data);
	if (!new_line)
		return (NULL);
	new_line = expand(new_line, lst_env);
	if (!new_line)
		return (NULL);
	replace_space(new_line, data);
	list = create_list(new_line, data);
	if (!list)
		return (NULL);
	return (list);
}

void	replace_space(char *line, t_data *data)
{
	int		i;
	int		check_quote;
	char	quote;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			check_quote = 0;
			quote = line[i];
			i++;
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

//skip quote b
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
				if (i > 1 && line[i] == quote && line[i - 1] == '\\')
					new_line[j++] = line[i++];
				else if (line[i] == quote)
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

//<< delimiteur < infile cat | cat "coucou le s" > outfile >> append		