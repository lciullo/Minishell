
#include "minishell.h"

int	implement_env(char **cmd, t_env *lst)
{
	if (cmd[1])
	{
		write(2, "subject : env with no options or arguments\n", 44);
		g_exit_status = 127;
		return (FAILURE);
	}
	if (!lst)
		return (FAILURE);
	list_print_env(lst);
	return (SUCCESS);
}
