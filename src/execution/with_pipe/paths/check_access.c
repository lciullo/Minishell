
#include "minishell.h"

static int	is_path(char *cmd);
static char	*get_cmd_with_paths(char **paths, char *cmd);
static	int	is_empty(int empty, char *cmd);

char	*check_cmd_access(char **paths, char *cmd, int empty)
{
	char	*cmd_with_path;
	char	*tmp;

	cmd_with_path = NULL;
	tmp = NULL;
	if (!paths)
		return (NULL);
	if (cmd[0] == '\0' || empty == 0)
		if (is_empty(empty, cmd) == FAILURE)
			return (NULL);
	if (!ft_strcmp(cmd, ".") || !ft_strcmp(cmd, ".."))
		return (NULL);
	if (is_path(cmd) == SUCCESS)
	{
		tmp = ft_strdup(cmd);
		if (!tmp)
			return (NULL);
		return (tmp);
	}
	cmd_with_path = get_cmd_with_paths(paths, cmd);
	if (!cmd_with_path)
		return (NULL);
	return (cmd_with_path);
}

static int	is_path(char *cmd)
{
	if (ft_strchr(cmd, '/') != NULL)
		return (SUCCESS);
	return (FAILURE);
}

static char	*get_cmd_with_paths(char **paths, char *cmd)
{
	int		row;
	char	*join_slash;
	char	*cmd_with_path;

	row = 0;
	join_slash = NULL;
	cmd_with_path = NULL;
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

static	int	is_empty(int empty, char *cmd)
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
	return (SUCCESS);
}
