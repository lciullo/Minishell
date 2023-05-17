/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:21:28 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/17 14:45:32 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_path(char **env)
{
	char	*path;
	int		row;

	path = NULL;
	row = 0;
	while (env[row])
	{
		if (ft_strncmp("PATH=", env[row], 5) == 0)
			path = env[row];
		row++;
	}
	if (!path)
		return (NULL);
	path += 5;
	return (path);
}

char	*check_cmd_acess(char **paths, char *cmd)
{
	char	*join_slash;
	char	*cmd_with_path;
	int		row;

	row = 0;
	join_slash = NULL;
	cmd_with_path = NULL;
	if (cmd != NULL && access(cmd, X_OK) == 0)
		return (cmd);
	while (paths[row])
	{
		join_slash = ft_strjoin(paths[row], "/");
		if (!join_slash)
			return (NULL);
		cmd_with_path = ft_strjoin(join_slash, cmd);
		if (!cmd_with_path)
			return (free(join_slash), NULL);
		free(join_slash);
		if (access(cmd_with_path, X_OK) == 0)
			return (cmd_with_path);
		free(cmd_with_path);
		row++;
	}
	return (NULL);
}

int	get_path_env(t_exec *data, char **env)
{
	data->paths = find_path(env);
	if (!data->paths)
	{
		ft_putstr_fd("environment path not found\n", 2);
		return (-1);
	}
	data->env_path = ft_split(data->paths, ':');
	if (!data->env_path)
	{
		ft_putstr_fd("environment path not found\n", 2);
		return (-1);
	}
	return (0);
}
