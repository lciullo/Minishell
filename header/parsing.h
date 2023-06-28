/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:55:15 by cllovio           #+#    #+#             */
/*   Updated: 2023/06/28 11:28:25 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/headers/libft.h"

/*======================= ENUMERATION =======================*/
enum {
	MALLOC_ERR_PARS,
	MALLOC_ERR_MAIN,
	MALLOC_ERR_EXEC,
	REDIR_ERR,
	PIPE_ERR,
	QUOTE_ERR,
};

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

/*======================= STRUCTURES =======================*/

typedef struct s_expand {
	t_env	*env;
	char	*line;
	char	*new_line;
	char	quote;
}	t_expand;

typedef struct s_data {
	t_env	*lst_env;
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

/*======================= PARSING =======================*/

/* ---- parsing.c ----*/
t_list	*parsing(char *line, t_data *data, t_env *lst_env);
void	print_error(int error_code);

/* ---- check_error.c ----*/
bool	check_error(t_data *data);

/*======================= EXPAND =======================*/

/* ---- expand.c ----*/
char	*expand(t_expand *utils, int i, int start, int here_doc);

/* ---- is_there_a_dollar.c ----*/
char	**is_there_a_dollar(char **tab, t_env *env, int	*status_expand);

/* ---- should_we_expand.c ----*/
int		should_we_expand(t_list **list, t_env *env);

/* ---- utils_expand.c ----*/
void	init_struct_expand(char *line, t_env *lst_env, t_expand *utils);
char	*get_var(t_expand *utils, int *i);
void	change_quote(char *value, int type);

/* ---- handle_different_case_expand.c ----*/
int		handle_quotes(t_expand *utils, int *i, int *start, int here_doc);
int		handle_dollar_sign(t_expand *utils, int *i, int *start, int here_doc);

/*======================= UTILS_PARSING =======================*/

/* ---- ft_split_parsing.c ----*/
char	**ft_split_parsing(char const *s);

/* ---- ft_split_parsing.c ----*/
char	*ft_strjoin_parsing(char *s1, char *s2);
char	*ft_strjoin_expand(char*s1, char *s2, int start, int i);

/* ---- skip.c ----*/
void	skip_quote(char *line, int *i, char quote);
int		skip_ws(char	*line);
int		skip_ws_i(char	*line, int i);
int		skip_redir(char *line, int *i, char redir, t_data *data);

/* ---- utils_parsing.c ----*/
void	init_structure(t_data *data, t_env *lst_env, char *line);
bool	is_builtins(char *cmd);
bool	is_white_space(char c);
bool	if_check(int type, char *line, int i);

/*======================= LIST =======================*/

/* ---- create_list.c ----*/
t_list	*create_list(t_data *data, t_env *env, char **tab_line);

/* ---- prepare_list_creation.c ----*/
char	**prepare_line_for_list(t_data *data);

/*======================= LIST/CHANGE_LIST =======================*/

/* ---- change_list.c ----*/
int		change_list(t_list **list, t_env *env, t_data *data, char **tab_line);

/* ---- add_space.c ----*/
char	*add_space(char	*line, int status, int malloc_size);

/* ---- change_order.c ----*/
char	**change_order(char **tab, t_data *data);

/* ---- change_tab.c ----*/
void	change_tab(char **tab_line, int type);
void	replace_space(char *line, int i);

/* ---- del_delimiteur.c ----*/
void	del_delimiteur(t_list **list);

/* ---- delete_quote.c ----*/
char	*is_there_a_quote(char *row);

#endif