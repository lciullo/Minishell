#include "minishell.h"

void	clear_in_child(t_exec *data, t_env **lst, t_list *list)
{
	ft_close(data->infile);
	ft_close(data->outfile);
	if (list)
		ft_lstclear(&data->head, free);
	if (lst)
		ft_lstclear_env(lst, free);
	free_struct(data);
	if (data->env)
		free_array(data->env);
}
