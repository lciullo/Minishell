#include "minishell.h"

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
