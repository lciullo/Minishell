/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:54:30 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/25 17:53:28 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/wait.h>
# include "../libft/headers/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include <sys/stat.h>

# define END "\033[0m"
# define BLUE "\033[1;34m"

extern int	g_exit_status;

enum {
	FAILURE = -1,
	BREAK = -6,
	SUCCESS = 2,
	ONLY_HEREDOC = -2,
	PLUS = 3,
	EQUAL = 4,
	NO_EQUAL = 5,
};

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

typedef struct s_exec
{
	int		nb_pids;
	int		exec_progress;
	int		end;
	int		infile;
	int		outfile;
	int		in_dir;
	int		out_dir;
	int		expand;
	int		nb_block;
	int		nb_cmd;
	int		nb_builtin;
	int		nb_heredoc;
	int		nb_args;
	int		quote_here_doc;
	int		*fd_heredoc;
	pid_t	*pids;
	pid_t	pid_heredoc;
	int		tmp_fd_heredoc[2];
	int		new_fd[2];
	int		old_fd[2];
	char	*cmd_with_path;
	char	*cmd;
	char	*paths;
	char	**env_path;
	char	**env;
	t_list	*head;
}	t_exec;

typedef struct s_export
{
	int	in_env;
	int	equal;
	int	plus;
}	t_export;

typedef struct s_expand {
	t_env	*env;
	char	*line;
	char	*new_line;
	char	quote;
}	t_expand;

/* ---- utils_main.c ----*/
void	empty_line_prompt(char *line, t_env *lst);
char	*get_line_and_init_signal(char *prompt_name);

/*======================= PARSING =======================*/
t_list	*parsing(char *line, t_data *data, t_env *lst_env);
void	print_error(int error_code);
bool	check_error(t_data *data);
char	*expand(t_expand *utils, int i, int start, int here_doc);
char	**is_there_a_dollar(char **tab, t_env *env, int	*status_expand);
int		should_we_expand(t_list **list, t_env *env);
void	init_struct_expand(char *line, t_env *lst_env, t_expand *utils);
char	*get_var(t_expand *utils, int *i);
void	change_quote(char *value, int type);
int		handle_quotes(t_expand *utils, int *i, int *start, int here_doc);
int		handle_dollar_sign(t_expand *utils, int *i, int *start, int here_doc);
char	**ft_split_parsing(char const *s);
char	*ft_strjoin_parsing(char *s1, char *s2);
char	*ft_strjoin_expand(char*s1, char *s2, int start, int i);
void	skip_quote(char *line, int *i, char quote);
int		skip_ws(char	*line);
int		skip_ws_i(char	*line, int i);
int		skip_redir(char *line, int *i, char redir, t_data *data);
void	init_structure(t_data *data, t_env *lst_env, char *line);
bool	is_builtins(char *cmd);
bool	is_white_space(char c);
bool	if_check(int type, char *line, int i);
t_list	*create_list(t_data *data, t_env *env, char **tab_line);
char	**prepare_line_for_list(t_data *data);
int		change_list(t_list **list, t_env *env, t_data *data, char **tab_line);
char	*add_space(char	*line, int status, int malloc_size);
char	**change_order(char **tab, t_data *data);
void	change_tab(char **tab_line, int type);
void	replace_space(char *line, int i);
void	del_delimiteur(t_list **list);
char	*is_there_a_quote(char *row);

//# ======================= EXECUTION ======================= #
int		init_struct(t_list *list, t_env *lst, t_exec *data, t_data *parsing);
void	free_struct(t_exec *data);
void	execution(t_list *t_list, t_data *parsing, t_exec *data, t_env **lst);
int		execution_core(t_list *list, t_exec *data, t_env **lst);
int		launch_exec(t_exec *data, t_list *list, t_env **lst);
int		execution_of_token(t_exec *data, t_list *list, t_env **lst);
int		loop_pipe_by_pipe(t_list *list, t_exec	*data, t_env **lst);
int		get_path_env(t_exec *data);
char	*check_cmd_access(char **paths, char *cmd, int empty);
int		is_executable(char *cmd, t_exec *data, t_list *list, t_env **lst);
int		dup_files(t_exec *data);
void	clear_cmd_not_found(t_exec *data);
void	close_cmd_not_found(t_exec *data);
void	clear_is_executable(t_exec *data, t_list *list, t_env **lst);
void	clear_execve_issue(t_exec *data, t_list *list, t_env **lst);
void	clear_builtin_exec(t_exec *data, t_list *list, t_env **lst);
void	clear_only_redir(t_exec *data, t_list *list, t_env **lst);
void	clear_exec_files_issue(t_list *list, t_env **lst, t_exec *data);
void	ft_close(int fd);
void	close_between_commands(t_exec *data);
void	close_all_fds(t_exec *data);
void	clear_dup_issue(t_exec *data, t_list *list, t_env **lst);
void	clear_dup_issue_builtin(t_exec *data, t_list *list, t_env **lst);
void	get_builtin_and_exec(t_list *list, t_exec *data, t_env **lst);
int		one_builtin_exec(char **token, t_exec *data, t_env **lst, t_list *list);
void	clear_one_builtin_exec_files(t_exec *data);
void	clear_in_child(t_exec *data, t_env **lst, t_list *list);
void	heredoc_ctrl_c(int signal);
void	heredoc_new_line(int signal);
void	heredoc_signals(int signal);
int		loop_for_heredoc(t_list *list, t_exec *data, \
		t_data *parsing, t_env **lst);
void	loop_in_child_heredoc(t_exec *data, char *delimiter, \
		t_env **lst, t_list *list);
void	add_to_tab_heredoc(int *fd_heredoc, int fd);
void	init_signals_heredoc(void);
int		close_heredoc_list(t_list *list);
void	clear_store_heredoc_issue(t_exec *data);
void	clear_heredoc_main_process(t_exec *data);
void	clear_heredoc_end(t_exec *data, t_env **lst, t_list *list, int fd[2]);
void	close_tab_heredoc(t_exec *data);
void	fork_issue_heredoc(t_exec *data, int fd[2]);
void	itoa_heredoc_issue(t_exec *data, int fd[2]);
void	pipe_heredoc_issue(t_exec *data);
int		loop_for_infile(t_list *list, t_exec *data);
int		loop_for_outfile(t_list *list, t_exec *data);

//# ======================= BUILTINS ======================= #
void	loop_for_builtin(char **token, t_exec *data, t_env **lst);
void	implement_echo(char **cmd);
int		implement_cd(char **cmd, t_env **lst);
char	*find_old_path(char *actual_path, t_env **lst);
void	clear_actualise_pwd(char *actual_path, char *old_path);
int		implement_pwd(char **cmd);
void	implement_exit(char **cmd, t_exec *data);
void	implement_unset(char **token, t_env **lst);
size_t	get_nb_arguments(char **cmd);
void	error_message_cd(int type);
void	implement_env(char **cmd, t_env *lst);
size_t	begin_of_name(char *path);
char	**fill_env(t_env *lst);
t_env	*creat_env(char **env);
void	implement_export(char **token, t_env **lst);
int		print_export(t_env *lst);
int		len_of_name(char *row, t_export *stat);
char	*get_name_variable(char *row, t_export *stat);
char	*get_value_variable(char *row);
int		parse_name(char *name);
int		parse_value(char *value);
int		last_char(char *name);
int		first_char(char c);
int		is_valid_export(int c);
int		is_valid_syntax(char *name);
char	*remove_plus_in_name(char *name);
void	clear_export_end_according_cases(t_export *stat, \
		char *name, char *value);
int		search_and_replace_value(t_env *lst, char *name, \
		char *value, t_export *stat);
t_env	*add_back_with_equal(t_env **lst, char *name, char *value);
int		add_to_export(t_env **lst, char *name, \
		char *value, t_export *stat);
void	change_equal_to_one(t_env **lst, char *name);
int		check_name_by_name(char *token, t_env **lst, t_export *stat);
int		check_only_equal(char *token);
int		is_in_env(t_env *lst, char *name);

#endif