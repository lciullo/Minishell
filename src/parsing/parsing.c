/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:59:50 by cllovio           #+#    #+#             */
/*   Updated: 2023/04/19 14:23:15 by cllovio          ###   ########.fr       */
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

void	create_list(char *line, t_parsing *parsing)
{
	char **tab;
	
	(void)parsing;
	tab =  ft_split(line, ' ');
	if (!tab)
		return ;
	int	i = 0;
	while (tab[i])
	{
		printf("line %d : %s\n", i, tab[i]);
		i++;
	}	
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
