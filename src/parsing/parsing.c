/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisa <lisa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:59:50 by cllovio           #+#    #+#             */
/*   Updated: 2023/04/25 12:55:23 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

// static char	*add_space(char **line, t_parsing *parsing);
// static char	*replace_space(char *line, t_parsing *parsing);
// static void	create_list(char *line, t_parsing *parsing);
void	create_list(char *line, t_parsing *parsing);

int	parsing(char *line)
{
	
	t_parsing	parsing;
	char *new_line;
	
	(void)line;
	init_structure(&parsing);
	count_separator(line, &parsing);
	printf("nbr_pipe : %d\nnbr_quote : %d\nnbr_here_doc : %d\nnbr_append : %d\nnbr_input : %d\nnbr_output : %d\nnbr_redir : %d\n", parsing.nbr_pipe, parsing.nbr_quote, parsing.nbr_here_doc, parsing.nbr_append, parsing.nbr_input, parsing.nbr_output, parsing.nbr_redir);
	printf("%s\n", line);
	new_line = replace_space(line, &parsing);
	new_line = add_space(line, &parsing);
	printf("\n%s\n\n", new_line);
	create_list(new_line, &parsing);
	return (0);
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

void	change_tab(char **tab_line)
{
	int	i;
	int	j;
	char	quote;
	
	i = 0;
	j = 0;
	while(tab_line[i])
	{
		if(tab_line[i][0] == 34 || tab_line[i][0] == 39)
		{
			j = 0;
			quote = tab_line[i][0];
			while(tab_line[i][j])
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

void	create_list(char *line, t_parsing *parsing)
{
	char	**tab_line;

	(void)parsing;
	tab_line = ft_split(line, ' ');
	if (!tab_line)
		return ;
	change_tab(tab_line);
	print_tab(tab_line);
}

//<< delimiteur < infile cat | cat "coucou le s" > outfile >> append