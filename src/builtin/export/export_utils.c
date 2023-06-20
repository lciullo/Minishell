#include "minishell.h"

char	*remove_plus_in_name(char *name)
{
	char	*to_find;

	to_find = NULL;
	if (last_char(name) == PLUS)
	{
		to_find = ft_strndup(to_find, name, (unsigned int)ft_strlen(name) - 1);
		if (!to_find)
			return (NULL);
		return (to_find);
	}
	return (name);
}

/*if (row[0] == '=' && row[1] == '\0')
		return ((int)ft_strlen(row));
if (row[0] == '=')
	{
		ft_dprintf(2, "export: not a valid identifier\n");
		return (FAILURE);
	}*/

static	int	len_of_name(char *row, t_export *stat)
{
	int	len;

	len = 0;
	if (row[0] == '\0')
	{
		ft_dprintf(2, "export: not a valid identifier\n");
		g_exit_status = 1;
		return (FAILURE);
	}
	while (row[len] != '\0' && row[len] != '=')
		len++;
	if (row[len] != '\0' && row[len] == '=')
		stat->equal = TRUE;
	if (row[len - 1] != '\0' && row[len - 1] == '+')
		stat->plus = TRUE;
	if (stat->equal == FALSE && stat->plus == TRUE)
	{
		ft_dprintf(2, "export: not a valid identifier\n");
		g_exit_status = 1;
		return (FAILURE);
	}
	if (stat->plus == TRUE && stat->equal == TRUE)
		return (len - 1);
	else if (stat->plus == FALSE && stat->equal == TRUE)
		return (len);
	else if (stat->plus == FALSE && stat->equal == FALSE)
		return (len);
	return (SUCCESS);
}

char	*get_name_variable(char *row, t_export *stat)
{
	char		*name;
	int			start;

	name = NULL;
	start = len_of_name(row, stat);
	if (start == FAILURE)
		return (NULL);
	name = ft_strndup(name, row, start);
	if (!name)
		return (NULL);
	return (name);
}

char	*get_value_variable(char *row)
{
	size_t		start;
	char		*value;

	value = NULL;
	start = begin_of_name(row);
	value = ft_strndup(value, &row[start + 1], ft_strlen(row));
	if (!value)
		return (NULL);
	return (value);
}

void	change_equal_to_one(t_env **lst, char *name)
{
	while (*lst != NULL)
	{
		if ((ft_strcmp((*lst)->name, name) == 0))
		{
			if ((*lst)->equal == 0)
				(*lst)->equal = 1;
		}
		*lst = (*lst)->next;
	}
}



