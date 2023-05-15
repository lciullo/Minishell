/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:41:00 by cllovio           #+#    #+#             */
/*   Updated: 2023/05/15 11:45:19 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/headers/libft.h"

typedef struct s_data {
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
}	t_data;

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
t_list	*parsing(char *line, t_data *data);

/* ---- utils_parsing.c ----*/
void	init_structure(t_data *data);
int		is_white_space(char	*line, int i);
void	change_tab(char **tab_line);
void	change_list(t_list **list);
char	*delete_quote(char *line, int j);

/* ---- list.c ----*/
t_list	*create_list(char *line, t_data *data);

/* ---- print.c ----*/
void	print_list(t_list	*a);
void	print_tab(char **tab);
void	list_print(t_list *lst);

int	check_error(char *line, t_data *data);

#endif