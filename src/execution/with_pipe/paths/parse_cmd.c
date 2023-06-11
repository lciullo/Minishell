/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 11:17:09 by lciullo           #+#    #+#             */
/*   Updated: 2023/06/11 14:15:17 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_path(char **env)
{
	char	*path;
	int		row;

	path = NULL;
	row = 0;
	if (!env)
		return (NULL);
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

int	is_executable(char *cmd)
{
	struct stat	info;

	if (stat(cmd, &info) == 0)
	{
		if (!(info.st_mode & S_IXUSR))
		{
			ft_dprintf(2, "minishell: %s: Permission denied\n", cmd);
			return (-1);
		}
		if (S_ISDIR(info.st_mode))
		{
			ft_dprintf(2, "%s, is a directory\n", cmd);
			return (-1);
		}
		return (0);
	}
	ft_dprintf(2, "No such file or directory\n");
	return (-1);
}

static int	is_path(char *cmd)
{
	if (ft_strchr(cmd, '/') != NULL)
		return (1);
	return (-1);
}

char	*check_cmd_access(char **paths, char *cmd)
{
	char	*join_slash;
	char	*cmd_with_path;
	int		row;

	row = 0;
	join_slash = NULL;
	cmd_with_path = NULL;
	if (!paths)
		return (NULL);
	if (cmd[0] == '\0')
		return (NULL);
	if (cmd != NULL && is_path(cmd) == 1)
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

int	get_path_env(t_exec *data)
{
	data->paths = find_path(data->env);
	if (!data->paths)
	{
		perror("Environment path not found");
		return (0);
	}
	data->env_path = ft_split(data->paths, ':');
	if (!data->env_path)
	{
		perror("issue in split to find environnement");
		return (-1);
	}
	return (0);
}
