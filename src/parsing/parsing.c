/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
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
void	create_node(char **tab, t_parsing *parsing);

int	parsing(char **line)
{
	//char	*new_line;
	t_parsing	parsing;
	(void)line;
	init_structure(&parsing);
	//count_separator(line, &parsing);
	//printf("nbr_pipe : %d\nnbr_quote : %d\nnbr_here_doc : %d\nnbr_append : %d\nnbr_input : %d\nnbr_output : %d\nnbr_redir : %d\n", parsing.nbr_pipe, parsing.nbr_quote, parsing.nbr_here_doc, parsing.nbr_append, parsing.nbr_input, parsing.nbr_output, parsing.nbr_redir);
	//new_line = add_space(line, &parsing);
	//new_line = replace_space(new_line, &parsing);
	//printf("\nnew_line : %s\n\n", new_line);
	//create_list(new_line, &parsing);
	return (0);
}



// }

//<< delimiteur < infile cat | cat "coucou le s" > outfile >> append