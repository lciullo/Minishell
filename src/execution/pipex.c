/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 09:29:41 by lciullo           #+#    #+#             */
/*   Updated: 2023/04/18 16:27:16 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*t_pipex		data;

	init_struct(&data);
	check_files(av[1], av[ac -1], &data);
	if (get_path_env(&data, env) == -1)
		return (0);
	exec_cmd(&data, av, env);
	close_files(&data);
	waitpid(data.pid1, NULL, 0);
	waitpid(data.pid2, NULL, 0);
	free_env_path(&data);*/

#include "minishell.h"

void	call_perror(t_pipex *data)
{
	close_files(data);
	free_env_path(data);
	free_cmds_and_paths(data);
	perror("execve");
	exit (1);
}

void	execution(char *line, char **env)
{
	/*t_pipex		data;

	init_struct(&data);
	check_files(av[1], av[ac -1], &data);
	if (get_path_env(&data, env) == -1)
		return (0);
	exec_cmd(&data, av, env);
	close_files(&data);
	waitpid(data.pid1, NULL, 0);
	waitpid(data.pid2, NULL, 0);
	free_env_path(&data);*/
	(void)env;
	(void)line;
}
