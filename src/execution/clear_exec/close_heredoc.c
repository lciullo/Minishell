#include "minishell.h"

int	close_for_heredoc(t_list *list)
{
	while (list != NULL)
	{
		if (list->type == HERE_DOC)
		{
			ft_close(ft_atoi(list->data[0]));
		}
		list = list->next;
	}
	return (0);
}

void	close_tab_heredoc(t_exec *data)
{
	int	i;

	i = 0;
	while (i < data->nb_heredoc)
	{
		ft_close(data->fd_heredoc[i]);
		i++;
	}
}
