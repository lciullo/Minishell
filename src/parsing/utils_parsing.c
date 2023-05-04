/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:04:05 by cllovio           #+#    #+#             */
/*   Updated: 2023/05/03 14:50:12 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_structure(t_parsing *parsing)
{
	parsing->nbr_pipe = 0;
	parsing->nbr_quote = 0;
	parsing->nbr_here_doc = 0;
	parsing->nbr_append = 0;
	parsing->len_line = 0;
	parsing->nbr_input = 0;
	parsing->nbr_output = 0;
	parsing->nbr_redir = 0;
	parsing->start = 0;
	parsing->end = 0;
}
int	is_white_space(char	*line, int i)
{
	if (line[i + 1])
		i++;
	while (line[i] && ((line[i] >= 9 && line[i] <= 13) || line[i] == ' '))
		i++;
	return (i);
}

void	count_separator(char *line, t_parsing *parsing)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if ((line[i] == 34 || line[i] == 39) && line[is_white_space(line, i) + 1])
			parsing->nbr_quote++;
		else if (line[is_white_space(line, i) + 1] && line[i] == '|')
			parsing->nbr_pipe++;
		else if (line[i] == '>' && line[i + 1] == '>'  && line[i - 1] != '>' && line[is_white_space(line, i + 1) + 1])
			parsing->nbr_append++;
		else if (line[i] == '<' && line[i + 1] == '<'  && line[i - 1] != '<' && line[is_white_space(line, i + 1) + 1])
			parsing->nbr_here_doc++;
		else if (line[is_white_space(line, i) + 1] && line[i] == '>' && line[i + 1] != '>'  && line[i - 1] != '>')
			parsing->nbr_output++;
		else if (line[is_white_space(line, i) + 1] && line[i] == '<' && line[i + 1] != '<'  && line[i - 1] != '<')
			parsing->nbr_input++;
		i++;
	}
	parsing->len_line = i;
	parsing->nbr_redir = parsing->nbr_here_doc + parsing->nbr_output + parsing->nbr_append + parsing->nbr_input;
}

char	*replace_space(char *line, t_parsing *parsing)
{
	int		i;
	int 	check_quote;
	char	quote;

	i = 0;
	while(line[i++])
	{
		if (line[i] == 34 || line[i] == 39)
		{
			check_quote = 0;
			quote = line[i];
			i++;
			while (line[i] && check_quote == 0)
			{
				if (line[i] == quote)
				// && parsing->nbr_quote % 2 == 0)
					check_quote = 1;
				else if(line[i] == ' ')
					line[i] = -1;
				if (line[i] == 34 || line[i] == 39)
					parsing->nbr_quote--;
				i++;
			}
		}
	}
	return (line);
}

char		*check_separator(char *line, char*new_line, int i, int j)
{
	while (line[i])
	{
		if ((line[i] == '>' && line[i + 1] == '>'  && line[i - 1] != '>')\
		|| (line[i] == '<' && line[i + 1] == '<'  && line[i - 1] != '<'))
		{
			new_line[j++] = ' ';
			new_line[j++] = line[i++];
			new_line[j++] = line[i];
			new_line[j] = ' ';	
		}
		else if (line[i] == '|' || (line[i] == '>' && line[i + 1] != '>'  && line[i - 1] != '>')\
		|| (line[i] == '<' && line[i + 1] != '<'  && line[i - 1] != '<'))
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

char	*add_space(char	*line, t_parsing *parsing)
{
	char 	*new_line;
	
	new_line = malloc(sizeof(char) * (parsing->len_line + \
	((parsing->nbr_pipe * 2 + parsing->nbr_redir * 2)) + 1));
	if (!new_line)
		return (NULL);
	new_line = check_separator(line, new_line, 0, 0);
	return (new_line);
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s | ", tab[i]);
		i++;
	}
}