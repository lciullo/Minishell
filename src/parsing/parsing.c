/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:41:46 by cllovio           #+#    #+#             */
/*   Updated: 2023/05/10 11:18:56 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	count_separator(char *line, t_data *data);
static void	replace_space(char *line, t_data *data);
static char	*add_space(char	*line, t_data *data);
static char	*check_separator(char *line, char*new_line, int i, int j);

t_list	*parsing(char *line)
{
	t_data	data;
	t_list		*list;
	char		*new_line;

	list = NULL;
	init_structure(&data);
	count_separator(line, &data);
	replace_space(line, &data);
	new_line = add_space(line, &data);
	if (!new_line)
		return (NULL); 
	list = create_list(new_line, &data);
	return (list);
}

static void	count_separator(char *line, t_data *data)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if ((line[i] == 34 || line[i] == 39))
			data->nbr_quote++;
		else if (line[i] == '|')
			data->nbr_pipe++;
		else if (line[i] == '>' && line[i + 1] == '>')
			data->nbr_append++;
		else if (line[i] == '<' && line[i + 1] == '<')
			data->nbr_here_doc++;
		else if (line[i] == '>' && line[i + 1] != '>' && line[i - 1] != '>')
			data->nbr_output++;
		else if (line[i] == '<' && line[i + 1] != '<' && line[i - 1] != '<')
			data->nbr_input++;
		i++;
	}
	data->len_line = i;
	data->nbr_redir = data->nbr_here_doc + \
	data->nbr_output + data->nbr_append + data->nbr_input;
}

static void	replace_space(char *line, t_data *data)
{
	int		i;
	int		check_quote;
	char	quote;

	i = 0;
	while (line[i++])
	{
		if (line[i] == 34 || line[i] == 39)
		{
			check_quote = 0;
			quote = line[i];
			i++;
			while (line[i] && check_quote == 0)
			{
				if (line[i] == quote)
					check_quote = 1;
				else if (line[i] == ' ')
					line[i] = -1;
				if (line[i] == 34 || line[i] == 39)
					data->nbr_quote--;
				i++;
			}
		}
	}
}
// && data->nbr_quote % 2 == 0)

static char	*add_space(char	*line, t_data *data)
{
	char	*new_line;

	new_line = malloc(sizeof(char) * (data->len_line + \
	((data->nbr_pipe * 2 + data->nbr_redir * 2)) + 1));
	if (!new_line)
		return (NULL);
	new_line = check_separator(line, new_line, 0, 0);
	return (new_line);
}

static char	*check_separator(char *line, char*new_line, int i, int j)
{
	while (line[i])
	{
		if ((line[i] == '>' && line[i + 1] == '>' && line[i - 1] != '>') \
		|| (line[i] == '<' && line[i + 1] == '<'))
		{
			new_line[j++] = ' ';
			new_line[j++] = line[i++];
			new_line[j++] = line[i];
			new_line[j] = ' ';	
		}
		else if (line[i] == '|' || (line[i] == '>' && \
		line[i + 1] != '>' && line[i - 1] != '>') \
		|| (line[i] == '<' && line[i + 1] != '<' && line[i - 1] != '<'))
		{
			new_line[j++] = ' ';
			new_line[j++] = line[i];
			new_line[j] = ' ';		
		}
		else
			new_line[j] = line[i];
		j++;
		i++;
	}
	new_line[j] = '\0';
	return (new_line);
}

//<< delimiteur < infile cat | cat "coucou le s" > outfile >> append		