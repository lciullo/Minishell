#include "minishell.h"

static void	search_and_delete(char *name, t_env *lst)
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

static int	is_valid(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') \
	|| (c >= 'A' && c <= 'Z') || (c == '_'))
		return (SUCCESS);
	else
		return (FAILURE);
}

int	parse_unset(char *value)
{
	size_t	i;

	i = 0;
	if (!value || value[0] == '\0')
	{
		ft_dprintf(2, "export : not a valid identifier\n");
		return (FAILURE);
	}
	if (value[0] != '\0')
	{
		if (value[0] == '-')
		{
			ft_dprintf(2, "Invalid option, subject : unset with no options\n");
			return (FAILURE);
		}
		if (first_char(value[0]) == FAILURE)
		{
			ft_dprintf(2, "export %s : not a valid identifier\n", value);
			return (FAILURE);
		}
	}
	while (value[i] != '\0')
	{
		if (is_valid(value[i]) == FAILURE)
		{
			ft_dprintf(2, "export %s : not a valid identifier\n", value);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int	implement_unset(char **token, t_env **lst)
{
	int	i;

	i = 1;
	while (token[i] != NULL)
	{
		if (parse_unset(token[i]) == SUCCESS)
			search_and_delete(token[i], *lst);
		i++;
	}
	return (SUCCESS);
}
