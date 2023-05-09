/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:04:05 by cllovio           #+#    #+#             */
/*   Updated: 2023/05/09 10:17:06 by cllovio          ###   ########.fr       */
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

void	change_tab(char **tab_line)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (tab_line[i])
	{
		if (tab_line[i][0] == 34 || tab_line[i][0] == 39)
		{
			j = 0;
			quote = tab_line[i][0];
			while (tab_line[i][j])
			{
				if (tab_line[i][j] == -1)
					tab_line[i][j] = ' ';
				j++;
			}
			if (tab_line[i][j - 1] == quote)
				tab_line[i] = delete_quote(tab_line[i], j);
		}
		i++;
	}
}

void	change_list(t_list **list)
{
	t_list	*temp;

	temp = (*list);
	while (temp)
	{
		if (temp->data[0][0] == '>' && temp->data[0][1] == '>')
			temp->next->type = APPEND;
		else if (temp->data[0][0] == '<' && temp->data[0][1] == '<')
			temp->next->type = HERE_DOC;
		else if (temp->data[0][0] == '<' && temp->data[0][1] == '\0')
			temp->next->type = INFILE;
		else if (temp->data[0][0] == '>' && temp->data[0][1] == '\0')
			temp->next->type = OUTFILE;
		else if (temp->data[0][0] == '|')
			temp->type = PIPE;
		else if (temp->type == -1 && \
		(temp->data[0][0] != '>' || temp->data[0][0] != '<'))
			temp->type = TOKEN;
		temp = temp->next;
	}
}

char	*delete_quote(char *line, int j)
{
	char	*new_line;
	int		i;
	int		k;

	new_line = malloc(sizeof(char) * (j - 2 + 1));
	if (!new_line)
		return (NULL);
	i = 0;
	k = 1;
	while (k < j - 1)
	{		
		new_line[i] = line[k];
		i++;
		k++;
	}
	new_line[i] = '\0';
	return (new_line);
}