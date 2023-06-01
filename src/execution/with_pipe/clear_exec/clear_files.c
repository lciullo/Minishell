#include "minishell.h"

void	clear_exec_files_issu(t_list *list, t_env *lst, t_exec *data)
{
	close_all_fds(data);
	close_tab(data);
	free_struct(data);
	ft_lstclear(&list, free);
	ft_lstclear_env(&lst, free);
}