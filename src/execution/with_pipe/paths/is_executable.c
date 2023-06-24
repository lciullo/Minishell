#include "minishell.h"

int	is_executable(char *cmd, t_exec *data, t_list *list, t_env **lst)
{
	struct stat	info;
	char	*str;

	str = NULL;
	if (stat(cmd, &info) == 0)
	{
		if (!(info.st_mode & S_IXUSR))
		{
			g_exit_status = 126;
			str = ft_strjoin(cmd, " : Permission denied\n");
			if (!str)
			{
				perror("Malloc failed in is executable");
				clear_is_executable(data, list, lst);
				return (FAILURE);
			}
			clear_is_executable(data, list, lst);
			write(2, str, ft_strlen(str));
			free(str);
			return (FAILURE);
		}
		if (S_ISDIR(info.st_mode))
		{
			g_exit_status = 126;
			str = ft_strjoin(cmd, " : is a directory\n");
			if (!str)
			{
				perror("Malloc failed in is executable");
				clear_is_executable(data, list, lst);
				return (FAILURE);
			}
			clear_is_executable(data, list, lst);
			write(2, str, ft_strlen(str));
			free(str);
			return (FAILURE);
		}
		return (SUCCESS);
	}
	write(2, "No such file or directory\n", 27);
	g_exit_status = 127;
	clear_is_executable(data, list, lst);
	return (FAILURE);
}
