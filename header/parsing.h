/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:41:00 by cllovio           #+#    #+#             */
/*   Updated: 2023/06/05 20:25:52 by cllovio          ###   ########.fr       */
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
	int		len_line;
	int		nbr_infile;
	int		nbr_outfile;
	int		nbr_redir;
	int		nbr_export;
	int		start;
	int		end;
}	t_data;

typedef	struct s_expand {
	t_env	**env;
	char	*line;
	char	*new_line;
}	t_expand;

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

/* ---- parsing.c ----*/
t_list	*parsing(char *line, t_data *data, t_env **lst_env);
bool	check_error(t_data *data);

/* ---- utils.c ----*/
void	init_structure(t_data *data, t_env **lst_env, char *line);
void	change_tab(char **tab_line);
bool	is_builtins(char *cmd);

/* ---- check_error.c ----*/
bool	check_wrong_character(char *line);
bool	check_quote(char *line);
int		nbr_quote(char *line, int *i, char quote);
bool	check_pipe(char	*line);
bool	check_redir(char *line, t_data *data);

/* ---- change_line.c ----*/
char	*change_line(t_data *data);

/* ---- add_space.c ----*/
char	*add_space(char	*line, t_data *data);

/* ---- expand.c ----*/
char	*expand(char *line, t_env **lst_env);

/* ---- utils_expand.c ----*/
char	*check_var(char *name_var, t_env **lst_env, char *new_line);
char	*ft_strjoin_b(char*s1, char *s2, int start, int i);

/* ---- split_parsing.c ----*/
char	**ft_split_parsing(char const *s);
bool	is_white_space(char c);

/* ---- change_order.c ----*/
char	**change_order(char **tab, t_data *data);

/* ---- list.c ----*/
t_list	*create_list(t_data *data, char **tab_line);

/* ---- change_list.c ----*/
void	change_list(t_list **list);
void	parse_line_for_quote(t_list **list);

/* ---- delete_quote.c ----*/
char	*is_there_a_quote(char *row);

/* ---- skip.c ----*/
void	skip_quote(char *line, int *i, char quote);
int	skip_white_space(char	*line);
int	skip_white_space_2(char	*line, int i);
int	skip_redir(char *line, int *i, char redir, t_data *data);

/* ---- print.c ----*/
void	print_list(t_list	*a);
void	print_tab(char **tab);
void	list_print(t_list *lst);
#endif
