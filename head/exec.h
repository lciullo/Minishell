/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:40:53 by cllovio           #+#    #+#             */
/*   Updated: 2023/04/24 16:56:58 by lciullo          ###   ########.fr       */
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
}	t_exec;

void	execution(char *line, char **env);

//# ======== Temporary ======== #

void	loop_for_heredoc(t_list **lst, char *delimiter);

void	loop_for_infile(t_list **lst);

//# ======== Builtins ======== #

void	loop_for_builtin(t_list **lst);

int		implement_echo(char **echo);

int		implement_cd(char **cd);

int		implement_pwd(char **pwd);

int		implement_exit(char **exit);

//void	init_struct(t_pipex *data);

#endif