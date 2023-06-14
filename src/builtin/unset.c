#include "minishell.h"

static void search_and_delete(char *name, t_env *lst)
{
	t_env	*copy;
	t_env	*next_node;

	copy = lst;
	next_node = NULL;
	while (copy)
	{
		if (!ft_strcmp(copy->name, name))
		{
			next_node->next = copy->next;
			if (copy->name)
				free(copy->name);
			if (copy->value)
				free(copy->value);
			free(copy);
			return ;
		}
		next_node = copy;
		copy = copy->next;
	}
}

int implement_unset(char **token, t_env **lst)
{
	int	i;

	i = 1;
	if (token[1])
	{
		if (token[1][0] == '-')
		{
			ft_dprintf(2, "Invalid option, subject : unset with no options\n");
			return (FAILURE);
		}
	}
	while (token[i] != NULL)
	{
		search_and_delete(token[i], *lst);
		i++;
	}
	return (SUCCESS);
}