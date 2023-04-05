/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 09:29:41 by lciullo           #+#    #+#             */
/*   Updated: 2023/04/05 14:43:13 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	call_perror(t_pipex *data)
{
	close_files(data);
	free_env_path(data);
	free_cmds_and_paths(data);
	perror("execve");
	exit (1);
}

int	main(int ac, char **av, char **env)
{
	t_pipex		data;

	if (ac != 5)
		return (ft_putstr_fd("put only 5 arguments\n", 2), 0);
	init_struct(&data);
	check_files(av[1], av[ac -1], &data);
	if (get_path_env(&data, env) == -1)
		return (0);
	exec_cmd(&data, av, env);
	close_files(&data);
	waitpid(data.pid1, NULL, 0);
	waitpid(data.pid2, NULL, 0);
	free_env_path(&data);
	return (0);
}
