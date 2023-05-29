/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:41:00 by cllovio           #+#    #+#             */
/*   Updated: 2023/05/29 15:33:15 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/headers/libft.h"
# include <stdbool.h>

typedef struct s_data {
	t_env	**lst_env;
	char	*line;
	int		nbr_pipe;
	int		nbr_quote;
	int		nbr_here_doc;
	int		nbr_append;
	int		nbr_infile;
	int		nbr_outfile;
	int		nbr_redir;
	int		nbr_export;
	int		start;
	int		end;
}	t_data;

enum {
	TOKEN,
	INFILE,
	OUTFILE,
	HERE_DOC,
	APPEND,
	PIPE,
	BUILTIN,
	EXPORT,
};

/* ---- change_list.c ----*/
void	change_list(t_list **list);
void	is_there_a_quote(t_list **list);
char	*delete_quote(char *line);
char	**change_order(char **tab);
void	change_order_redir(char **new_tab, char **tab, \
		int start, int end, int *i);
void	change_order_token(char **new_tab, char **tab, \
		int start, int end, int *i);

/* ---- check_error.c ----*/
bool	check_error(t_data *data);
bool	check_quote(char *line);
bool	check_pipe(char	*line);
int		nbr_quote(char *line, int *i, char quote);
bool	check_redir(char *line, t_data *data);

/* ---- list.c ----*/
t_list	*create_list(char *line, t_data *data);
t_list	*create_node(int	*start, int *end, char **tab_line);
void	find_malloc_size(char **tab, int *end, int *start, int *malloc_size);
void	fill_tab(char **tab_line, char **token, int *start, int *end);
void	del_delimiteur(t_list **list);

/* ---- parsing.c ----*/
t_list	*parsing(char *line, t_data *data, t_env **lst_env);
void	replace_space(char *line, t_data *data, int i);
char	*add_space(char	*line, t_data *data);
char	*check_separator(char *line, char*new_line, int i, int j);

/* ---- print.c ----*/
void	print_list(t_list	*a);
void	print_tab(char **tab);
void	list_print(t_list *lst);

/* ---- skip.c ----*/
void	skip_quote(char *line, int *i, char quote);
int		skip_white_space(char	*line);
int		skip_white_space_2(char	*line, int i);
int		skip_redir(char *line, int *i, char redir, t_data *data);

/* ---- utils_parsing.c ----*/
void	init_structure(t_data *data);
void	change_tab(char **tab_line);
bool	is_builtins(char *cmd);

char	**ft_split_parsing(char *s);
bool	is_white_space(char	c);
char	*expand(char *line, t_env **lst_env);
char	*change_line(t_data *data);
#endif