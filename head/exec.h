/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:40:53 by cllovio           #+#    #+#             */
/*   Updated: 2023/05/09 10:59:09 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../libft/headers/libft.h"

//# ======================= STRUCTURE ======================= #

typedef struct s_exec
{
	int	end;
	int	infile;
	int	outfile;
	int	expand;
	int	nb_cmds;
}	t_exec;

void	init_struct(t_exec *data);

//# ======================= EXECUTION ======================= #

void	execution(char *line, char **env, t_exec *data);

//# === One builtin execution  === #

int		one_builtin_exec(char **token, t_exec *data, char **env);

//# ======================= TEMPORARY ======================= #

void	tmp_lst(t_list **lst);

void	loop_for_heredoc(t_list **lst, char *delimiter);

void	loop_for_infile(t_list **lst, t_exec *data);

void	loop_for_outfile(t_list **lst, t_exec *data);

//# ======================= BUILTINS ======================= #

void	loop_for_builtin(char **token, t_exec *data, char **env);

int		is_builtin(char **token);

int		implement_env(char **env);

int		implement_echo(char **cmd);

int		implement_cd(char **cmd);

int		implement_pwd(char **cmd);

int		implement_exit(char **cmd, t_exec *data);

#endif