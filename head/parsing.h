/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:41:00 by cllovio           #+#    #+#             */
/*   Updated: 2023/05/09 10:26:17 by cllovio          ###   ########.fr       */
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

/* ---- parsing.c ----*/
t_list	*parsing(char *line);

/* ---- utils_parsing.c ----*/
void	init_structure(t_parsing *parsing);
int		is_white_space(char	*line, int i);
void	change_tab(char **tab_line);
void	change_list(t_list **list);
char	*delete_quote(char *line, int j);

/* ---- list.c ----*/
t_list	*create_list(char *line, t_parsing *parsing);

/* ---- print.c ----*/
void	print_list(t_list	*a);
void	print_tab(char **tab);
void	list_print(t_list *lst);

#endif