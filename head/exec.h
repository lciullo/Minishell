/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:40:53 by cllovio           #+#    #+#             */
/*   Updated: 2023/05/11 16:50:12 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../libft/headers/libft.h"

//# ======================= STRUCTURE ======================= #

typedef struct s_exec
{
	int		end;
	int		infile;
	int		outfile;
	int		expand;
	int		nb_cmds;
	char	*cmd_with_path;
	char	*cmd;
	char	*paths;
	char	**env_path;
}	t_exec;

void	init_struct(t_list *list, t_exec *data);

//# ======================= EXECUTION ======================= #

void	execution(t_list *t_list, char **env, t_data *parsing, t_exec *data);

int		execution_core(t_list *list, t_data *parsing, t_exec *data, char **env);

//# === One builtin execution  === #

int		one_builtin_exec(char **token, t_exec *data, char **env);

//# === Loop many pipe === #

int		loop_pipe_by_pipe(t_list *list, t_data *parsing, \
									t_exec	*data, char **env);

//# === Execute token  === #

//# --- Find path in environnement ---#

int		get_path_env(t_exec *data, char **env);

//# --- Check access ---#

char	*check_cmd_acess(char **paths, char *cmd);

//# ======================= MANAGEMENT FILES ======================= #

void	loop_for_heredoc(t_list **list, char *delimiter);

void	loop_for_infile(t_list *list, t_exec *data);

void	loop_for_outfile(t_list *list, t_exec *data);

//# ======================= BUILTINS ======================= #

void	loop_for_builtin(char **token, t_exec *data, char **env);

int		is_builtin(char **token);

int		implement_env(char **env);

int		implement_echo(char **cmd);

int		implement_cd(char **cmd);

int		implement_pwd(char **cmd);

int		implement_exit(char **cmd, t_exec *data);

//# ======================= TEMPORARY ======================= #

//# --- Print debug --- #

void	exec_print_list(t_list *lst);

#endif