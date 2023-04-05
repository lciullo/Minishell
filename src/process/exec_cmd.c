/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 09:28:05 by lciullo           #+#    #+#             */
/*   Updated: 2023/03/14 11:34:44 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	dupe_cmd1(t_pipex *data)
{
	if (dup2(data->infile, STDIN_FILENO) == -1)
	{
		free_env_path(data);
		exit(1);
	}
	else if (data->check_infile == 0)
		close(data->infile);
	if (dup2(data->fd[1], STDOUT_FILENO) == -1)
	{
		free_env_path(data);
		exit(1);
	}
	else
		close(data->fd[1]);
}

static void	dupe_cmd2(t_pipex *data)
{
	if (dup2(data->fd[0], STDIN_FILENO) == -1)
	{
		free_env_path(data);
		exit(1);
	}
	else
		close(data->fd[0]);
	if (dup2(data->outfile, STDOUT_FILENO) == -1)
	{
		free_env_path(data);
		exit(1);
	}
	else
		close(data->outfile);
}

void	exec_cmd1(t_pipex *data, char **av, char **env)
{
	if (data->fd[0])
		close(data->fd[0]);
	dupe_cmd1(data);
	data->cmds_array = ft_split(av[2], ' ');
	if (!data->cmds_array)
	{
		close_files(data);
		free_env_path(data);
		exit(1);
	}
	data->cmd = get_cmd(data->env_path, data->cmds_array[0]);
	if (!data->cmd)
	{
		close_files(data);
		free_env_path(data);
		free_cmds_and_paths(data);
		exit(1);
	}
	execve(data->cmd, data->cmds_array, env);
	call_perror(data);
}

void	exec_cmd2(t_pipex *data, char **av, char **env)
{
	if (data->fd[1])
		close(data->fd[1]);
	dupe_cmd2(data);
	data->cmds_array = ft_split(av[3], ' ');
	if (!data->cmds_array)
	{
		close_files(data);
		ft_putstr_fd("malloc crash\n", 2);
		free_env_path(data);
		exit(1);
	}
	data->cmd = get_cmd(data->env_path, data->cmds_array[0]);
	if (!data->cmd)
	{
		close_files(data);
		free_env_path(data);
		free_cmds_and_paths(data);
		ft_putstr_fd("command not found\n", 2);
		exit(1);
	}
	execve(data->cmd, data->cmds_array, env);
	call_perror(data);
}

int	exec_cmd(t_pipex *data, char **av, char **env)
{
	if (pipe(data->fd) < 0)
		exit(1);
	data->pid1 = fork();
	if (data->pid1 == 0)
		exec_cmd1(data, av, env);
	data->pid2 = fork();
	if (data->pid2 == 0)
		exec_cmd2(data, av, env);
	return (0);
}
