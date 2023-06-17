
#include "minishell.h"


int	implement_pwd(char **cmd)
{
	char	*current_directory_path;

	current_directory_path = NULL;
	if (cmd[1])
	{
		if (cmd[1][0] == '-')
		{
			ft_dprintf(2, "Invalid option, subject : pwd with no options\n");
			g_exit_status = 2;
			return (FAILURE);
		}
	}
	current_directory_path = getcwd(NULL, 0);
	if (current_directory_path == NULL)
	{
		ft_dprintf(2, "pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
		g_exit_status = 0;
		return (errno);
	}
	ft_dprintf(2, "getcwd return %s\n", current_directory_path);
	if (current_directory_path)
	{
		ft_dprintf(1, "%s\n", current_directory_path);
		free(current_directory_path);
	}
	g_exit_status = 0;
	return (0);
}
