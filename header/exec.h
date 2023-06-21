
#ifndef EXEC_H
# define EXEC_H

# include "../libft/headers/libft.h"

//# ======================= STRUCTURE ======================= #

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


int				init_struct(t_list *list, t_env *lst, \
							t_exec *data, t_data *parsing);

void			free_struct(t_exec *data);

//# ======================= BOOLEAN ======================= #

//# ======================= EXECUTION ======================= #

int				execution(t_list *t_list, t_data *parsing, \
								t_exec *data, t_env **lst);

int				execution_core(t_list *list, t_exec *data, t_env **lst);

//# ==================== With Pipe =================== #

int				launch_exec(t_exec *data, t_list *list, t_env **lst, char **env);

int				execution_of_token(t_exec *data, t_list *list, t_env **lst, char **env);

//# === Loop many pipe === #

int				loop_pipe_by_pipe(t_list *list, t_exec	*data, t_env **lst);

//# ============== Execute token =============== #

//# === Little parsing of execution === # 

//# --- Find path in environnement ---#

int				get_path_env(t_exec *data);

//# --- Check access ---#

char			*check_cmd_access(char **paths, char *cmd, int empty);

//# --- Check if is executable ---#

int				is_executable(char *cmd, t_exec *data, t_list *list, t_env **lst);

//# --- Dup files ---#

int				dup_files(t_exec *data);

//# === Clear token  === #

//# --- Command not found --- #

void			clear_cmd_not_found(t_exec *data, t_list *list, t_env **lst);

void			close_cmd_not_found(t_exec *data);

//# --- Is executable --- #

void			clear_is_executable(t_exec *data, t_list *list, t_env **lst);

//# --- Execve issue --- #

void			clear_execve_issue(t_exec *data, t_list *list, t_env **lst);

//# --- Clear builtin execution --- #

void			clear_builtin_exec(t_exec *data, t_list *list, t_env **lst);

//# --- Execve issue --- #

void			clear_only_redir(t_exec *data, t_list *list, t_env **lst, char **env);

//# --- Files issue --- #

void			clear_exec_files_issue(t_list *list, t_env **lst, t_exec *data);

//# === Clear between commands and when they are issues  === #

//# --- Close ---#

void			ft_close(int fd);

void			close_between_commands(t_exec *data);

void			close_all_fds(t_exec *data);

//# --- Dup issue --- #

void			clear_dup_issue(t_exec *data, t_list *list, t_env **lst);

void			clear_dup_issue_builtin(t_exec *data, t_list *list, t_env **lst);

//# ==================== Without Pipe =================== #

//# === One builtin execution  === #

void			get_builtin_and_exec(t_list *list, t_exec *data, t_env **lst);

int				one_builtin_exec(char **token, t_exec *data, t_env **lst, t_list *list);

void			clear_one_builtin_exec_files(t_exec *data);

//# ======================= MANAGEMENT FILES ======================= #

//# === Heredoc === #

void			heredoc_ctrl_c(int signal);

void			heredoc_new_line(int signal);

void			heredoc_signals(int signal);

int				loop_for_heredoc(t_list *list, t_exec *data, t_data *parsing, t_env **lst);

void			loop_in_child_heredoc(t_exec *data, char *delimiter, t_env **lst, t_list *list);

void			add_to_tab_heredoc(int *fd_heredoc, int fd);

void 			init_signals_heredoc(void);

//# === Clear heredoc  === #

int				close_heredoc_list(t_list *list);

void 			clear_store_heredoc_issue(t_exec *data);

void			clear_heredoc_main_process(t_exec *data);

void 			clear_heredoc_end(t_exec *data, t_env **lst, t_list *list, int fd[2]);

void			close_tab_heredoc(t_exec *data);

void			fork_issue_heredoc(t_exec *data, int fd[2]);

void			itoa_heredoc_issue(t_exec *data, int fd[2]);

void			pipe_heredoc_issue(t_exec *data);

//# === Infile outfile === #

int				loop_for_infile(t_list *list, t_exec *data);

int				loop_for_outfile(t_list *list, t_exec *data);

//# ======================= BUILTINS ======================= #

void			loop_for_builtin(char **token, t_exec *data, t_env **lst);

int				implement_echo(char **cmd);

int				implement_cd(char **cmd, t_env **lst);

int				implement_pwd(char **cmd);

int				implement_exit(char **cmd, t_exec *data);

int				implement_unset(char **token, t_env **lst);

//# --- Environnement--- #

int				implement_env(char **cmd, t_env *lst);

size_t			begin_of_name(char *path);

char			**fill_env(t_env *lst, int *malloc_check);

t_env			*creat_env(char **env);

//# --- Export --- #

int				implement_export(char **token, t_env **lst);

//# Export without arguments #

int				print_export(t_env *lst);

//# Export with arguments #

char			*get_name_variable(char *row, t_export *stat);

char			*get_value_variable(char *row);

int				parse_name(char *name);

int				parse_value(char *value);

int				last_char(char *name);

int				first_char(char c);

char			*remove_plus_in_name(char *name);

//# Manage case with equal in name #

int				search_and_replace_value(t_env *lst, char *name, char *value, t_export *stat);

t_env			*add_back_with_equal(t_env **lst, char *name, char *value);

int				add_to_export(t_env **lst, char *name, char *value, t_export *stat);

void			change_equal_to_one(t_env **lst, char *name);

//# ======================= TEMPORARY ======================= #

//# --- Print debug --- #

void			exec_print_list(t_list *lst);

#endif