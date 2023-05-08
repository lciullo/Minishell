/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:41:00 by cllovio           #+#    #+#             */
/*   Updated: 2023/05/05 16:11:49 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/headers/libft.h"

typedef struct s_parsing {
	int	nbr_pipe;
	int	nbr_quote;
	int	nbr_here_doc;
	int	nbr_append;
	int	len_line;
	int	nbr_input;
	int	nbr_output;
	int	nbr_redir;
	int	start;
	int	end;
}	t_parsing;

enum {
	TOKEN,
	INFILE,
	OUTFILE,
	HERE_DOC,
	APPEND,
	PIPE,
	BUILTIN,
};

/* ---- utils_parsing.c ----*/
void	init_structure(t_parsing *parsing);
void	count_separator(char *line, t_parsing *parsing);
char	*replace_space(char *line, t_parsing *parsing);
char	*add_space(char	*line, t_parsing *parsing);
void	print_tab(char **tab);
t_list	*parsing(char *line);
void	print_list(t_list	*a);

#endif