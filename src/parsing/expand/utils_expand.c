#include "minishell.h"

static char	*check_var(char *name_var, t_env *lst_env, char *new_line);

void	init_struct_expand(char *line, t_env *lst_env, t_expand *utils)
{
	utils->line = line;
	utils->env = lst_env;
	utils->new_line = ft_calloc(1, 1);
}

char	*get_var(t_expand *utils, int *i)
{
	int		start;
	int		j;
	char	*name_var;

	j = 0;
	if (utils->line[*i] == '$')
		*i = *i + 1;
	start = *i;
	while (utils->line[*i] && (ft_isalnum(utils->line[*i]) == true \
	|| utils->line[*i] == '_'))
		*i = *i + 1;
	name_var = malloc(sizeof(char) * ((*i - start) + 1));
	if (!(name_var))
		return (free(utils->new_line), NULL);
	while (start < *i)
	{
		name_var[j] = utils->line[start];
		j++;
		start++;
	}
	name_var[j] = '\0';
	utils->new_line = check_var(name_var, utils->env, utils->new_line);
	if (!(utils->new_line))
		return (free(name_var), NULL);
	return (free(name_var), utils->new_line);
}

static char	*check_var(char *name_var, t_env *lst_env, char *new_line)
{
	char	*value;

	while (lst_env)
	{
		if (ft_strcmp(name_var, lst_env->name) == 0)
		{
			value = ft_strdup(lst_env->value);
			if (!value)
				return (NULL);
			change_quote(value, 0);
			new_line = ft_strjoin_parsing(new_line, value);
			free(value);
			if (!(new_line))
				return (NULL);
			return (new_line);
		}
		lst_env = lst_env->next;
	}
	return (new_line);
}

void	change_quote(char *value, int type)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (type == 0)
		{
			if (value[i] == '\"')
				value[i] = -1;
			else if (value[i] == '\'')
				value[i] = -2;
		}
		if (type == 1)
		{
			if (value[i] == -1)
				value[i] = '\"';
			if (value[i] == -2)
				value[i] = '\'';
		}
		i++;
	}
}
