/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:59:50 by cllovio           #+#    #+#             */
/*   Updated: 2023/04/21 14:36:24 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

// 34 = "
// 39 = '
char	*replace_space(char *line, t_parsing *parsing)
{
	int		i;
	int 	check_quote;
	char	quote;
	
	i = 0;
	while(line[i])
	{
		if (line[i] == 34 || line[i] == 39)
		{
			check_quote = 0;
			quote = line[i];
			i++;
			while (line[i] && check_quote == 0)
			{
				if (line[i] == quote && parsing->nbr_quote % 2 == 0)
					check_quote = 1;
				else if(line[i] == ' ')
					line[i] = -1;
				if (line[i] == 34 || line[i] == 39)
					parsing->nbr_quote--;
				i++;
			}
		}
		i++;
	}
	return(line);
}

void	count_separator(char **line, t_parsing *parsing)
{
	while(line[0][parsing->len_line])
	{
		if (line[0][parsing->len_line] == 34 || line[0][parsing->len_line] == 39)
			parsing->nbr_quote++;
		if (line[0][parsing->len_line] == '|')
			parsing->nbr_pipe++;
		if (line[0][parsing->len_line] == '>' || line[0][parsing->len_line] == '<')
			parsing->nbr_redir++;
		parsing->len_line++;
	}
}

char	*realloc_line(char **line, t_parsing *parsing)
{
	char 	*new_line;
	int		i;
	int		j;
	
	new_line = malloc(sizeof(char) * (parsing->len_line + (parsing->nbr_pipe * 2) + 1));
	if (!new_line)
		return (NULL);
	i = 0;
	j = 0;
	while (line[0][i])
	{
		if (line[0][i] == '|')
		{
			new_line[j] = ' ';
			j++;
			new_line[j] = line[0][i];
			j++;
			new_line[j] = ' ';		
		}
		else
			new_line[j] = line[0][i];
		i++;
		j++;
	}
	new_line[j] = '\0';
	return (new_line);
}

void	create_list_2(char **tab, t_parsing *parsing, int *j)
{
	int	tab_size;

	tab_size = 0;
	(void) parsing;
	while (tab[*j])
	{
		if (tab[*j][0] == '|' || tab[*j][0] == '<' || tab[*j][0] == '>')
		{
			if (tab_size == 0)
			{
				tab_size = 1;
				*j = *j + 1;
			}
			break ;
		}
		tab_size++;
		*j = *j + 1;
	}
	printf("tab_size : %d\n", tab_size);
	printf("j : %d\n", *j);
}
		// if (tab[parsing->i][0] == '|' || tab[parsing->i][0] == '<' || tab[parsing->i][0] == '>' ||
		// (tab[parsing->i][0] == '>' && tab[parsing->i][1] == '>') || (tab[parsing->i][0] == '<' && tab[parsing->i][1] == '<'))
		// {
		// 	if (tab_size == 0)
		// 		tab_size = 1;
		// 	break ;
		// }
		
void	create_list(char *line, t_parsing *parsing)
{
	char	**tab;
	int		nbr_node;

	tab =  ft_split(line, ' ');
	if (!tab)
		return ;
	int	i = 0;
	while (tab[i])
	{
		printf("line %d : %s\n", i, tab[i]);
		i++;
	}
	nbr_node =	((parsing->nbr_pipe * 2) + 1) + (parsing->nbr_redir * 2);
	printf("nbr_node : %d\n", nbr_node);
	parsing->i = 0;
	int	j;
	j = 0;
	while (nbr_node > 0)
	{
		create_list_2(tab, parsing, &j);
		nbr_node--;
	}
	printf("j : %d\n", j);
}

int	parsing(char **line)
{
	char	*new_line;
	t_parsing	parsing;

	init_structure(&parsing);
	count_separator(line, &parsing);
	new_line = realloc_line(line, &parsing);
	new_line = replace_space(new_line, &parsing);
	printf("new_line : %s\n", new_line);
	printf("nbr_pipe : %d\nnbr_quote : %d\nnbr_redir : %d\n", parsing.nbr_pipe, parsing.nbr_quote, parsing.nbr_redir);
	create_list(new_line, &parsing);
	return (0);
}
