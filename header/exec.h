/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:40:53 by cllovio           #+#    #+#             */
/*   Updated: 2023/05/30 15:49:44 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../libft/headers/libft.h"

//# ======================= STRUCTURE ======================= #

typedef struct s_exec
{
	int		index;
	int		i;
	int		end;
	int		infile;
	int		outfile;
	int		in_dir;
	int		out_dir;
	int		expand;
	int		nb_cmds;
	int		nb_builtin;
	int		*fd_heredoc;
	pid_t	*pids;
	pid_t	pid_heredoc;
	int		new_fd[2];
	int		old_fd[2];
	int		prev_fd;
	char	*cmd_with_path;
	char	*cmd;
	char	*paths;
	char	**env_path;
}	t_exec;

void		init_struct(t_list *list, t_exec *data);

void		free_struct(t_exec *data);

//# ======================= BOOLEAN ======================= #

//# ======================= EXECUTION ======================= #

void		execution(t_list *t_list, char **env, t_data *parsing, \
						t_exec *data, t_env *lst_env);

int			execution_core(t_list *list, t_exec *data, char **env, t_env *lst_env);

//# ==================== With Pipe =================== #

int			launch_exec(t_exec *data, t_list *list, t_env *lst_env, char **env);

//# === Loop many pipe === #

int			loop_pipe_by_pipe(t_list *list, t_exec	*data, char **env, t_env *lst_env);

//# === Execute token  === #

//# --- Find path in environnement ---#

int			get_path_env(t_exec *data, char **env);

//# --- Dup files ---#

int			dup_files(t_exec *data);

//# --- Close ---#

void		ft_close(int fd);

void		close_cmd_not_found(t_exec *data);

int			close_for_heredoc(t_list *list);

void		close_tab(t_exec *data, t_list *list);

//# --- Check access ---#

char		*check_cmd_acess(char **paths, char *cmd);

//# ==================== Without Pipe =================== #

//# === One builtin execution  === #

void		get_builtin_and_exec(t_list *list, t_exec *data, t_env *lst_env);

int			one_builtin_exec(t_list *list, char **token, t_exec *data, t_env *lst_env);

//# ======================= MANAGEMENT FILES ======================= #

void		loop_for_heredoc(t_list *list, t_exec *data, t_env **lst_env);

int			loop_for_infile(t_list *list, t_exec *data);

int			loop_for_outfile(t_list *list, t_exec *data);

//# ======================= BUILTINS ======================= #

void		loop_for_builtin(char **token, t_exec *data, t_env *lst_env);

t_env		*creat_env(char **env);

int			is_builtin(char **token);

int			implement_env(t_env *lst_env);

int			implement_echo(char **cmd);

int			implement_cd(char **cmd);

int			implement_pwd(char **cmd);

int			implement_exit(char **cmd, t_exec *data);

int			implement_export(char **token, t_exec *data, t_env *lst_env);

//# ======================= TEMPORARY ======================= #

//# --- Print debug --- #

void		exec_print_list(t_list *lst);

//# ======================= FREE AND CLOSE ======================= #

//# --- Dup issu --- #

void		clear_dup_issu(t_exec *data, t_list *list, t_env *lst_env);

//# --- Command not found --- #

void		clear_cmd_not_found(t_exec *data, t_list *list, t_env *lst_env);

//# --- Files issu --- #

void		clear_files_issu(t_exec *data, t_list *list, t_env *lst_env);

void		clear_execve_issu(t_exec *data, t_list *list, t_env *lst_env);

#endif