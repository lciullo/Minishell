/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:40:53 by cllovio           #+#    #+#             */
/*   Updated: 2023/05/02 15:10:19 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../libft/headers/libft.h"

//# ======== Struct ======== #

typedef struct s_exec
{
	int	expand;
	int	infile;
	int	outfile;
	int	end;
}	t_exec;



void	execution(char *line, char **env, t_exec *data);

//# ======== Temporary ======== #

void	loop_for_heredoc(t_list **lst, char *delimiter);

void	loop_for_infile(t_list **lst, t_exec *files);

void	loop_for_outfile(t_list **lst, t_exec *files);

//# ======== Builtins ======== #

void	loop_for_builtin(t_list **lst, t_exec *data, char **env);

int		is_builtin(t_list **lst);

int		implement_env(char **env);

int		implement_echo(char **cmd);

int		implement_cd(char **cmd);

int		implement_pwd(char **cmd);

int		implement_exit(char **cmd, t_exec *data);

//void	init_struct(t_pipex *data);

#endif