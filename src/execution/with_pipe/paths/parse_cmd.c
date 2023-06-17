
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

int	is_executable(char *cmd, t_exec *data, t_list *list, t_env **lst)
{
	struct stat	info;

	if (stat(cmd, &info) == 0)
	{
		if (!(info.st_mode & S_IXUSR))
		{
			ft_dprintf(2, "minishell: %s: Permission denied\n", cmd);
			g_exit_status = 126;
			clear_is_executable(data, list, lst);
			return (-1);
		}
		if (S_ISDIR(info.st_mode))
		{
			ft_dprintf(2, "%s, is a directory\n", cmd);
			g_exit_status = 126;
			clear_is_executable(data, list, lst);
			return (-1);
		}
		return (0);
	}
	ft_dprintf(2, "No such file or directory\n");
	g_exit_status = 127;
	clear_is_executable(data, list, lst);
	return (-1);
}

static int	is_path(char *cmd)
{
	if (ft_strchr(cmd, '/') != NULL)
		return (1);
	return (-1);
}

char	*check_cmd_access(char **paths, char *cmd, int empty)
{
	char	*join_slash;
	char	*cmd_with_path;
	char	*tmp;
	int		row;

	row = 0;
	join_slash = NULL;
	cmd_with_path = NULL;
	tmp = NULL;
	if (!paths)
		return (NULL);
	if (cmd[0] == '\0' || empty == 0)
	{
		if (empty == 0)
		{
			g_exit_status = 0;
			return (NULL);
		}
		else if (cmd[0] == '\0')
		{
			g_exit_status = 127;
			return (NULL);
		}
	}
	if (!ft_strcmp(cmd, ".") || !ft_strcmp(cmd, ".."))
		return (NULL);
	if (is_path(cmd) == 1)
	{
		tmp = ft_strdup(cmd);
		return (tmp);
	}
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
