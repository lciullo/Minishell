/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:40:53 by cllovio           #+#    #+#             */
/*   Updated: 2023/06/11 11:34:55 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int		*fd_heredoc;
	pid_t	*pids;
	pid_t	pid_heredoc;
	int		new_fd[2];
	int		old_fd[2];
	char	*cmd_with_path;
	char	*cmd;
	char	*paths;
	char	**env_path;
}	t_exec;

typedef struct s_export
{
	int	in_env;
	int	equal;
	int	plus;
}	t_export;


int				init_struct(t_list *list, t_exec *data, t_data *parsing);

void			free_struct(t_exec *data);

//# ======================= BOOLEAN ======================= #

//# ======================= EXECUTION ======================= #

int				execution(t_list *t_list, char **env, t_data *parsing, \
							t_exec *data, t_env **lst);

int				execution_core(t_list *list, t_exec *data, char **env, t_env **lst);

//# ==================== With Pipe =================== #

int				launch_exec(t_exec *data, t_list *list, t_env **lst, char **env);

//# === Loop many pipe === #

int				loop_pipe_by_pipe(t_list *list, t_exec	*data, char **env, \
									t_env **lst);

//# ============== Execute token =============== #

//# === Little parsing of execution === # 

//# --- Find path in environnement ---#

int				get_path_env(t_exec *data, char **env);

//# --- Check access ---#

char			*check_cmd_access(char **paths, char *cmd);

//# --- Check if is executable ---#

int				is_executable(char *cmd);

//# --- Dup files ---#

int				dup_files(t_exec *data);

//# === Clear token  === #

//# --- Command not found --- #

void			clear_cmd_not_found(t_exec *data, t_list *list, t_env **lst);

void			close_cmd_not_found(t_exec *data);

//# --- Execve issue --- #

void			clear_execve_issue(t_exec *data, t_list *list, t_env **lst);

//# --- Clear builtin execution --- #

void			clear_builtin_exec(t_exec *data, t_list *list, t_env **lst);

//# --- Files issue --- #

void			clear_exec_files_issu(t_list *list, t_env **lst, t_exec *data);

//# === Clear between commands and when they are issues  === #

//# --- Close ---#

void			ft_close(int fd);

void			close_between_commands(t_exec *data);

void			close_all_fds(t_exec *data);

//# --- Dup issue --- #

void			clear_dup_issue(t_exec *data, t_list *list, t_env **lst);

//# ==================== Without Pipe =================== #

//# === One builtin execution  === #

void			get_builtin_and_exec(t_list *list, t_exec *data, t_env **lst);

int				one_builtin_exec(t_list *list, char **token, t_exec *data, \
							t_env **lst);

//# ======================= MANAGEMENT FILES ======================= #

//# === Heredoc === #

void			heredoc_ctr_c(int signal);

void			heredoc_new_line(int signal);

int				loop_for_heredoc(t_list *list, t_exec *data, t_env **lst);

void			add_to_tab(int *fd_heredoc, int fd);

//# === Clear heredoc  === #

int				close_for_heredoc(t_list *list);

void			close_tab(t_exec *data);

void			fork_issue_heredoc(t_exec *data, int fd[2]);

void			itoa_heredoc_issue(t_exec *data, int fd[2]);

void			pipe_heredoc_issue(t_exec *data);

//# === Infile outfile === #

int				loop_for_infile(t_list *list, t_exec *data);

int				loop_for_outfile(t_list *list, t_exec *data);

//# ======================= BUILTINS ======================= #

void			loop_for_builtin(char **token, t_exec *data, t_env **lst);

t_env			*creat_env(char **env);

int				is_builtin(char **token);

int				implement_env(t_env *lst);

int				implement_echo(char **cmd);

int				implement_cd(char **cmd);

int				implement_pwd(char **cmd);

int				implement_exit(char **cmd, t_exec *data);

//# --- Environnement--- #

int				implement_env(t_env *lst);

size_t			begin_of_name(char *path);

//# --- Export --- #

int				implement_export(char **token, t_env **lst);

//# Export without arguments #

int				print_export(t_env *lst);

//# Export with arguments #

char			*get_name_variable(char *row, t_export *stat);

char			*get_value_variable(char *row);

int				parse_name(char *name);

int				is_equal(char *name);

int				last_char(char *name);

char			*remove_plus_in_name(char *name);

//# Manage case with equal in name #

int				search_and_replace_value(t_env *lst, char *name, char *value, t_export *stat);

t_env			*add_back_with_equal(t_env *lst, char *name, char *value);

int				add_to_export(t_env **lst, char *name, char *value, t_export *stat);

void			change_equal_to_zero(t_env *lst, char *name);

void			change_equal_to_one(t_env *lst, char *name);

//# ======================= TEMPORARY ======================= #

//# --- Print debug --- #

void			exec_print_list(t_list *lst);

#endif