#include "minishell.h"

static int	del_delimiteur_1(t_list **list);

void	del_delimiteur(t_list **list)
{
	int	is_it_done;

	is_it_done = 0;
	while (is_it_done != 1)
		is_it_done = del_delimiteur_1(list);
}

static int	del_delimiteur_1(t_list **list)
{
	t_list	*current;
	t_list	*previous;

	current = *list;
	previous = NULL;
	while (current)
	{
		if (current->type == -1)
		{
			if (previous)
				previous->next = current->next;
			else
				*list = current ->next;
			free_array(current->data);
			free(current);
			return (0);
		}
		previous = current;
		current = current->next;
	}
	return (1);
}
