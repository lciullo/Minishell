
#include "minishell.h"

void	implement_env(char **cmd, t_env *lst)
{
	if (cmd[1])
	{
		write(2, "subject : env with no options or arguments\n", 44);
		g_exit_status = 127;
		return ;
	}
	if (!lst)
		return ;
	list_print_env(lst);
	return ;
}
