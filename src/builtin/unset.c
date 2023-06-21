#include "minishell.h"

static void	search_and_delete(char *name, t_env **lst)
{
	t_env	*it;
	t_env	*prev;

	it = *lst;
	prev = NULL;
	while (it)
	{
		if (!ft_strcmp(it->name, name))
		{
			if (prev)
				prev->next = it->next;
			else
				*lst = it->next;
			if (it->name)
				free(it->name);
			if (it->value)
				free(it->value);
			free(it);
			return ;
		}
		prev = it;
		it = it->next;
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
		return (ft_dprintf(2, "unset : not a valid identifier\n"), 1);
	if (value[0] != '\0')
	{
		if (value[0] == '-')
			return (ft_dprintf(2, "Invalid option, subject : unset with no options\n"), 2);
		if (first_char(value[0]) == FAILURE)
			return (ft_dprintf(2, "unset %s : not a valid identifier\n", value), 1);
	}
	while (value[i] != '\0')
	{
		if (is_valid(value[i]) == FAILURE)
			return (ft_dprintf(2, "unset %s : not a valid identifier\n", value), 1);
		i++;
	}
	return (0);
}

int	implement_unset(char **token, t_env **lst)
{
	int	i;
	int	exit_status;
	int	previous_exit_status;

	i = 1;
	exit_status = 0;
	previous_exit_status = 0;
	if (!lst)
		return (FAILURE);
	while (token[i] != NULL)
	{
		if (i != 1)
			previous_exit_status = exit_status;
		exit_status = parse_unset(token[i]);
		if ( exit_status == 0)
			search_and_delete(token[i], lst);
		if (previous_exit_status != 0 && exit_status == 0)
			exit_status = previous_exit_status;
		i++;
	}
	g_exit_status = exit_status;
	return (SUCCESS);
}
