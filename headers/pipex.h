/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:55:52 by lciullo           #+#    #+#             */
/*   Updated: 2023/03/20 11:11:06 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include <sys/wait.h>

# include <stdio.h>

# include "../libft/headers/libft.h"

//# ======== Struct ======== #

typedef struct s_pipex
{
	int		pid1;
	int		pid2;
	int		fd[2];
	int		infile;
	int		outfile;
	int		check_infile;
	int		check_outfile;
	char	*paths;
	char	**env_path;
	char	**cmds_array;
	char	*cmd;
}	t_pipex;

void	init_struct(t_pipex *data);

void	free_struct(t_pipex *data);

//# ======== Parsing ======== #

//# ---- Files ---- #

int		check_files(char *infile, char *outfile, t_pipex *data);

//# ---- Check path and commands ---- #

int		get_path_env(t_pipex *data, char **env);

char	*get_cmd(char **paths, char *cmd);

void	call_perror(t_pipex *data);

//# ======== Manage process ======== #

int		exec_cmd(t_pipex *data, char **av, char **env);

void	exec_cmd1(t_pipex *data, char **av, char **env);

void	exec_cmd2(t_pipex *data, char **av, char **env);

//# ======== Free and close all ======== #

void	close_files(t_pipex *data);

void	free_env_path(t_pipex *data);

void	free_cmds_and_paths(t_pipex *data);

#endif