#include "minishell.h"

static char	*find_path(char **env);

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
