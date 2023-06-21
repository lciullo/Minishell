
#include "minishell.h"

static int	is_path(char *cmd);

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
/// access

static int check_empty_access(char **paths, char *cmd, int empty)
{
	if (!paths)
		return (FAILURE);
	if (cmd[0] == '\0' || empty == 0)
	{
		if (empty == 0)
		{
			g_exit_status = 0;
			return (FAILURE);
		}
		else if (cmd[0] == '\0')
		{
			g_exit_status = 127;
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

static char *join_cmd_with_path(char **paths, char *cmd)
{
	char	*join_slash;
	char	*cmd_with_path;
	int		row;

	join_slash = NULL;
	cmd_with_path = NULL;
	row = 0;
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
	return (cmd_with_path);
}

char	*check_cmd_access(char **paths, char *cmd, int empty)
{
	char	*cmd_with_path;
	char	*tmp;

	cmd_with_path = NULL;
	tmp = NULL;
	if (check_empty_access(paths, cmd, empty) == FAILURE)
		return (NULL);
	if (!ft_strcmp(cmd, ".") || !ft_strcmp(cmd, ".."))
		return (NULL);
	if (is_path(cmd) == 1)
	{
		tmp = ft_strdup(cmd);
		return (tmp);
	}
	cmd_with_path = join_cmd_with_path(paths, cmd);
	if (!cmd_with_path)
		return (NULL);
	return (NULL);
}
