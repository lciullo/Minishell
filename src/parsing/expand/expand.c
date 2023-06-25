#include "minishell.h"

static int	end_of_expand(t_expand *utils, int i, int start);
static int	handle_quotes(t_expand *utils, int *i, int *start, int here_doc);
static int	handle_dollar_sign(t_expand *utils, int *i, int *start);
static int	handle_special_case(t_expand *utils, int *i);

//je securise end_of_Expand 
char	*expand(t_expand *utils, int i, int start, int here_doc)
{
	while (utils->line[i])
	{
		if (utils->line[i] == '\"' || utils->line[i] == '\'')
		{
			utils->quote = utils->line[i];
			if (handle_quotes(utils, &i, &start, here_doc) == FAILURE)
				return (NULL);
			if (utils->line[i] == utils->quote)
				i++;
		}
		else if (if_check(0, utils->line, i) == true)
		{
			if (handle_dollar_sign(utils, &i, &start) == FAILURE)
				return (NULL);
			start = i;
		}
		else if (utils->line[i])
			i++;
	}
	if (end_of_expand(utils, i, start) == FAILURE)
		return (NULL);
	return (utils->new_line);
}

// NULL CHECK
static int	end_of_expand(t_expand *utils, int i, int start)
{
	char	*temp;

	if (utils->line[start])
	{
		temp = utils->new_line;
		utils->new_line = ft_strjoin_expand(utils->new_line, \
		utils->line, start, i);
		free(temp);
		if (!utils->new_line)
			return (FAILURE);
	}
	return (SUCCESS);
}

static int	handle_quotes(t_expand *utils, int *i, int *start, int here_doc)
{
	if (utils->line[*i] == '\'' && here_doc == 0)
		skip_quote(utils->line, i, utils->line[*i]);
	else if (utils->line[*i] == '\"' || \
	(utils->line[*i] == '\'' && here_doc == 1))
	{
		if (utils->line[*i] == utils->quote)
			*i = *i + 1;
		while (utils->line[*i] && utils->line[*i] != utils->quote)
		{	
			if (if_check(1, utils->line, *i) == true)
			{
				if (handle_dollar_sign(utils, i, start) == FAILURE)
					return (FAILURE);
				*start = *i;
			}
			else if (utils->line[*i])
				*i = *i + 1;
		}
	}
	return (SUCCESS);
}

static int	handle_dollar_sign(t_expand *utils, int *i, int *start)
{
	char	*temp;

	if (*i - *start != 0)
	{
		temp = utils->new_line;
		utils->new_line = ft_strjoin_expand(utils->new_line, \
		utils->line, *start, *i);
		if (!(utils->new_line))
			return (free(temp), FAILURE);
		free(temp);
	}
	if (utils->line[*i + 1] == '$' || utils->line[*i + 1] == '?')
	{
		temp = utils->new_line;
		if (handle_special_case(utils, i) == FAILURE)
			return (free(temp), FAILURE);
	}
	else if (ft_isalpha(utils->line[*i + 1]) == 1 || utils->line[*i + 1] == '_')
	{
		temp = utils->new_line;
		utils->new_line = get_var(utils, i);
		if (!(utils->new_line))
			return (free(temp), FAILURE);
	}
	else
		*i = *i + 2;
	return (SUCCESS);
}

static int	handle_special_case(t_expand *utils, int *i)
{
	char	*str_exit_status;

	if (utils->line[*i + 1] == '$')
	{
		utils->new_line = ft_strjoin_parsing(utils->new_line, "$$");
		if (!(utils->new_line))
			return (FAILURE);
		*i = *i + 2;
	}
	else if (utils->line[*i + 1] == '?')
	{
		str_exit_status = ft_itoa(g_exit_status);
		if (!(str_exit_status))
			return (free(utils->new_line), FAILURE);
		utils->new_line = ft_strjoin_parsing(utils->new_line, str_exit_status);
		free(str_exit_status);
		if (!(utils->new_line))
			return (FAILURE);
		*i = *i + 2;
	}
	return (SUCCESS);
}