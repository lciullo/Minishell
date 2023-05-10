/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:41:46 by cllovio           #+#    #+#             */
/*   Updated: 2023/05/09 13:21:18 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	count_separator(char *line, t_parsing *parsing);
static char	*replace_space(char *line, t_parsing *parsing);
static char	*add_space(char	*line, t_parsing *parsing);
static char	*check_separator(char *line, char*new_line, int i, int j);

t_list	*parsing(char *line)
{
	t_parsing	parsing;
	t_list		*list;
	char		*new_line;

	list = NULL;
	init_structure(&parsing);
	count_separator(line, &parsing);
	new_line = replace_space(line, &parsing);
	new_line = add_space(line, &parsing);
	list = create_list(new_line, &parsing);
	return (list);
}

static void	count_separator(char *line, t_parsing *parsing)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if ((line[i] == 34 || line[i] == 39))
			parsing->nbr_quote++;
		else if (line[i] == '|')
			parsing->nbr_pipe++;
		else if (line[i] == '>' && line[i + 1] == '>')
			parsing->nbr_append++;
		else if (line[i] == '<' && line[i + 1] == '<')
			parsing->nbr_here_doc++;
		else if (line[i] == '>' && line[i + 1] != '>' && line[i - 1] != '>')
			parsing->nbr_output++;
		else if (line[i] == '<' && line[i + 1] != '<' && line[i - 1] != '<')
			parsing->nbr_input++;
		i++;
	}
	parsing->len_line = i;
	parsing->nbr_redir = parsing->nbr_here_doc + \
	parsing->nbr_output + parsing->nbr_append + parsing->nbr_input;
}

static char	*replace_space(char *line, t_parsing *parsing)
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
					parsing->nbr_quote--;
				i++;
			}
		}
	}
	return (line);
}
// && parsing->nbr_quote % 2 == 0)

static char	*add_space(char	*line, t_parsing *parsing)
{
	char	*new_line;

	new_line = malloc(sizeof(char) * (parsing->len_line + \
	((parsing->nbr_pipe * 2 + parsing->nbr_redir * 2)) + 1));
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