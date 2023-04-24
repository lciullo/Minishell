/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:59:50 by cllovio           #+#    #+#             */
/*   Updated: 2023/04/24 15:24:05 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static char	*add_space(char **line, t_parsing *parsing);
static char	*replace_space(char *line, t_parsing *parsing);
static void	create_list(char *line, t_parsing *parsing);
void	create_node(char **tab, t_parsing *parsing);
// void	create_list_2(char **tab, t_parsing *parsing, int *start)
// {
// 	int	tab_size;

// 	tab_size = 0;
// 	(void) parsing;
// 	while (tab[*end])
// 	{
// 		if (tab[*end][0] == '|' || tab[*end][0] == '<' || tab[*end][0] == '>')
// 		{
// 			if (tab_size == 0)
// 			{
// 				tab_size = 1;
// 				*end = *end + 1;
// 			}
// 			break ;
// 		}
// 		tab_size++;
// 		*end = *end + 1;
// 	}
// 	printf("tab_size : %d\n", tab_size);
// 	printf("end : %d\n", *end);
// }

int	parsing(char **line)
{
	char	*new_line;
	t_parsing	parsing;

	init_structure(&parsing);
	count_separator(line, &parsing);
	printf("nbr_pipe : %d\nnbr_quote : %d\nnbr_here_doc : %d\nnbr_append : %d\nnbr_input : %d\nnbr_output : %d\nnbr_redir : %d\n", parsing.nbr_pipe, parsing.nbr_quote, parsing.nbr_here_doc, parsing.nbr_append, parsing.nbr_input, parsing.nbr_output, parsing.nbr_redir);
	new_line = add_space(line, &parsing);
	new_line = replace_space(new_line, &parsing);
	printf("\nnew_line : %s\n\n", new_line);
	create_list(new_line, &parsing);
	return (0);
}

static char	*add_space(char **line, t_parsing *parsing)
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

static char	*replace_space(char *line, t_parsing *parsing)
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

static void	create_list(char *line, t_parsing *parsing)
{
	char	**tab;
	int		nbr_node;
	//t_list	*list;
	//t_list *new;
	
	tab =  ft_split(line, ' ');
	//list = NULL;
	if (!tab)
		return ;
	int	i = 0;
	while (tab[i])
	{
		printf("line %d : %s\n", i, tab[i]);
		i++;
	}
	printf("\n");
	nbr_node =	((parsing->nbr_pipe * 2) + 1) + (parsing->nbr_redir * 2);
	printf("nbr_node : %d\n", nbr_node);
	while (nbr_node > 0)
	{
		parsing->start = parsing->end;
	 	create_node(tab, parsing);
	 	//ft_lstadd_back(&list, new);
	 	nbr_node--;
	}
	//printf("end : %d\n", end);
}

void	create_node(char **tab, t_parsing *parsing)
{	
	//char **token;
	// int		i;

	// i = 0;
	while (tab[parsing->end])
	{
		if (tab[parsing->end][0] == '>' || tab[parsing->end][0] == '<' || tab[parsing->end][0] == '|')
			break ;
		else if (tab[parsing->end - 1][0] == '>' || tab[parsing->end - 1][0] == '<')
			break ;
		else if (tab[parsing->end + 1][0] == '|' || tab[parsing->end + 1][0] == '>' || tab[parsing->end + 1][0] == '<')
			break ;
		parsing->end++;
	}
	// token = malloc(sizeof(char *) * (parsing->end - parsing->start + 2));
	// if (!token)
	// 	return ;
	// while (parsing->end >= parsing->start)
	// {
	// 	ft_strcpy(token[i], tab[parsing->start]);
	// 	i++;
	// 	parsing->start++;
	// }
	printf("start : %d  | end : %d\n", parsing->start, parsing->end);
	if (tab[parsing->end][0] == '>' || tab[parsing->end][0] == '<' || tab[parsing->end][0] == '|' || tab[parsing->end - 1][0] == '>' || tab[parsing->end - 1][0] == '<' || tab[parsing->end + 1][0] == '|' || tab[parsing->end + 1][0] == '>' || tab[parsing->end + 1][0] == '<')
		parsing->end++;
}

//<< delimiteur < infile cat | cat "coucou le s" > outfile >> append